#ifndef RUNTIME_TYPE_H
#define RUNTIME_TYPE_H

#include "./function.h"
#include "./reference.h"
#include "./object.h"

enum class TypeKind {
    Function,
    Object,
    Type,
    Module,
    Namespace
};

class Type : public Object {
public:
    Type(TypeKind kind, const std::string& name) : kind(kind), name(name) {}

    /*
    This operator creates an instance of this Type object. In a call Type::operator()();
    the result is just another regular type object, derived classes (like String) should
    override this operator overload in order to instantiate string objects
    */
    virtual Object* operator()() {
        Object* obj = new Object();
        obj->setField("__type__", getType());
        return obj;
    }
private:
    TypeKind kind;
    std::string name;
public:
    static Reference* getType() {
        static OwnedReference typeOwner(new Type(TypeKind::Type, "type"));

        // bootstrap __type__ once
        static bool initialized = false;
        if (!initialized) {
            typeOwner->setField("__type__", new BorrowedReference(&typeOwner));
            initialized = true;
        }

        static BorrowedReference typeBorrow(&typeOwner);
        return &typeBorrow;
    }
};


#endif