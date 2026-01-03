#ifndef RUNTIME_NAMESPACE_H
#define RUNTIME_NAMESPACE_H

//#include "./reference.h"
#include "./object.h"


/*
A namespace is a collection of names mapped to object references. Every construct (except object variables) defines a namespace: 
class, function, enum, module. The global namespace is a special namespace whose parent namespace is null (i.e it is the top level namespace) thus, 
the namespace system forms a heirarchical structure. The runtime keeps track of namespaces and ensures that no namespace can access the names of its child
namespace. 
*/
class NameSpace : public Object {
public:
    NameSpace(NameSpace *parent = nullptr) : Object(TypeInfo::Namespace), parent(parent) {}

    void addName(const std::string& name, Reference* ref) {
        setField(name, ref);
    } 

    // just checks if the name is in the current namespace and doesnt check parent
    bool containsNameInCurrent(const std::string& name) const {
        return fields.find(name) != fields.end();
    }

    Reference* get(const std::string& name) {
        if (parent == nullptr) {
            if (! containsName(name)) throw NameException("unable to find name");
            return fields[name];
        } else if (containsNameInCurrent(name)) return fields[name];
        else {
            return parent->get(name);
        }
    }

    Reference* getInCurrent(const std::string& name) {
        if (! containsNameInCurrent(name)) throw NameException("no name in current namespace");
        return fields[name];
    }

    // also checks parent 
    bool containsName(const std::string& name) const {    
        if (parent == nullptr) {
            return containsNameInCurrent(name) ? true : false;
        }
        else if (containsNameInCurrent(name)) return true;
        else {
            return parent->containsName(name);
        }
    }

    void deleteName(const std::string& name) {
        if (containsNameInCurrent(name)) {
            delete fields[name];
            fields.erase(name);
        }
    }
    // calls Object::~Object() to clean up fields;
    ~NameSpace() = default;
private:    
    NameSpace *parent;
};

#endif