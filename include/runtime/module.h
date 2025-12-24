#ifndef RUNTIME_MODULE_H
#define RUNTIME_MODULE_H

#include <string>
#include <unordered_map>
#include "./exceptions.h"

enum class AccessMode {
    PUBLIC, PRIVATE, PACKAGE
};

enum class SymKind {
    FUNCTION, MODULE, OBJECT, CLASS, ENUM
};

struct SymInfo {
    std::string name;
    AccessMode mode;
    SymKind kind;

    SymInfo(const std::string& name, AccessMode mode, SymKind kind) : name(name), mode(mode), kind(kind) {}

    bool isPublic() const { return mode == AccessMode::PUBLIC; }
    bool isPrivate() const { return mode == AccessMode::PRIVATE; }
    bool isPackagePrivate() const { return mode == AccessMode::PACKAGE; }
};

// contains information about the names defined within the symbol table
class SymTable {
private:
    std::unordered_map<std::string, SymInfo> map;
public:
    SymTable() = default;

    void addSymbol(const std::string& name, SymInfo info) {
        if (map.count(name) != 0) throw NameException("cannot have two symbols with the same name");
        map[name] = info;
    }

    ~SymTable() = default;
};


#endif
