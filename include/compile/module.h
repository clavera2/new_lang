#ifndef COMPILE_MODULE_H
#define COMPILE_MODULE_H

#include <string>
#include <unordered_map>

// the address of a symbol in a module file
using Address =size_t;

// represents a kind of symbol
enum class SymType {
    VARIABLE,
    FUNCTION,
    TYPE,
    ENUM,
    MODULE
};

// represents a symbol
struct Sym {
    std::string name;
    SymType type;
    Address address;

    Sym(const std::string& name, SymType type, Address address) : name(name), type(type), address(address) {}
};  

struct SymTab {
    std::unordered_map<std::string, Sym> symbols;
};

// represents a compiled source file
class ModFile {
public:
private:
    std::string name;
    SymTab sym_table;
};

#endif