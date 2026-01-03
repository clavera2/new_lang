#ifndef RUNTIME_OBJECT_H
#define RUNTIME_OBJECT_H

#include <string>
#include "reference.h"
#include <unordered_map>

enum class TypeInfo {
    Function,
    Object,
    Type,
    Module,
    Namespace
};

class Object {
public: 
    Object(TypeInfo info) : info(info) {}
    Object(TypeInfo info, const std::unordered_map<std::string, Reference*>& fields) : info(info), fields(fields) {}
    bool containsField(const std::string& name);

    Reference* getField(const std::string& name);

    void setField(const std::string& name, Reference* r) {
        fields[name] = r; 
    } 

    bool is(TypeInfo info) const {
        return this->info == info;
    }

    ~Object();
protected:
    TypeInfo info;
    std::unordered_map<std::string, Reference*> fields;
};

#endif