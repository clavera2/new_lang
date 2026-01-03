#ifndef UTILS_H
#define UTILS_H

#include "./object.h"

// creates an object
Object* make(const std::unordered_map<std::string, Reference*>& fields) {
    return new Object(TypeInfo::Object, fields);
}



#endif