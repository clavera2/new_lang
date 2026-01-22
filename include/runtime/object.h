#ifndef RUNTIME_OBJECT_H
#define RUNTIME_OBJECT_H

#include <string>
#include "reference.h"
#include <unordered_map>

enum class TypeKind {
    Function,
    Object,
    Type,
    Module,
    Namespace
};

class Object {
public: 
    Object() = default;
    Object(const std::unordered_map<std::string, Reference*>& fields) : fields(fields) {}
    bool containsField(const std::string& name);

    Reference* getField(const std::string& name);

    void setField(const std::string& name, Reference* r) {
        fields[name] = r; 
    } 

    ~Object();
protected:
    std::unordered_map<std::string, Reference*> fields;
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

    static Reference* getType() {
        Type* type = new Type(TypeKind::Type, "type");
        type->setField("__type__", new NoneReference());
        static OwnedReference typeType(type);
        return new BorrowedReference(&typeType);
    }
};

#endif