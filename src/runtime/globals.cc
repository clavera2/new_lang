#include "./runtime/globals.h"

// the only namespace object whose parent should be null, other namespace objects must inherit from this namespace
NameSpace GLOBALS = NameSpace();

Type* type = new Type("type", new NoneReference());

void initGlobals() {
    // sets up the global namespace such as importing core modules, setting core types etc
    GLOBALS.addName("type", new OwnedReference(type));
}