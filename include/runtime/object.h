#ifndef RUNTIME_OBJECT_H
#define RUNTIME_OBJECT_H

#include <string>
#include "reference.h"
#include <unordered_map>

class Object {
public: 
    Object() = default;
    bool containsField(const std::string& name);

    Reference* getField(const std::string& name);

    void setField(const std::string& name, Reference* r) {
        fields[name] = r; 
    } 

    ~Object();
protected:
    std::unordered_map<std::string, Reference*> fields;
};

#endif