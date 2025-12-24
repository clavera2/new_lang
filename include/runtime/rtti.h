#ifndef RUNTIME_RTTI_H
#define RUNTIME_RTTI_H

#include <string>
#include <unordered_map>
#include "function.h"

struct Reference;

struct RTTI {
    std::string& type;
    std::unordered_map<std::string, InstanceMethod*> instanceMethods;
    std::unordered_map<std::string, StaticMethod *> staticMethods;
};

#endif