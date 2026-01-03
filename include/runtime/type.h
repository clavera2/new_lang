#ifndef RUNTIME_TYPE_H
#define RUNTIME_TYPE_H

#include "./function.h"

// set on an object field __type__
class Type : public Object {
public: 
    Type(const std::string& name, Reference* base) : Object(TypeInfo::Type), name(name), base(base) {}
    ~Type() {
        delete base; // safe because base should always be either a borrowed reference or none reference
    }
private:
    std::string name;
    Reference *base;
};

#endif