#ifndef RUNTIME_OBJECT_H
#define RUNTIME_OBJECT_H

#include "rtti.h"

class Object {
public:
    Object(RTTI* rtti);
    ~Object();

    bool containsField(const std::string& name);

    Reference* getField(const std::string& name);

    void setField(const std::string& name, Reference* r) {
        fields[name] = r; 
    } 
private:
    RTTI* rtti;
    std::unordered_map<std::string, Reference*> fields;
};


#endif