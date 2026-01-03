#ifndef RUNTIME_GLOBALS_H
#define RUNTIME_GLOBALS_H

#include "./module.h"
#include "./type.h"

// represents the global namespace
extern NameSpace GLOBALS;
// represents the base type object
extern Type type;

// initialize the global module object
void initGlobals();

#endif