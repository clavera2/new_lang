#ifndef RUNTIME_MODULE_H
#define RUNTIME_MODULE_H

#include <string>
#include <unordered_map>
#include "./exceptions.h"
#include "./namespace.h"


struct SynTab {

};

// a module is just a namespace as a file
class Module : public NameSpace {
public:
    Module(const std::string& name, NameSpace* parent = nullptr) : NameSpace(parent), name(name) {}
private:
    std::string name;
};

#endif
