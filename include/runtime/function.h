#ifndef RUNTIME_TYPES_H
#define RUNTIME_TYPES_H

#include "./type.h"
#include "./rt.h"
#include <vector>
#include <optional>

/*
Given a function definition in source code: 

add := function(x, y) {
    return x + y;
}

after compilation:

SymTab entry:
|  add |  #45 | -> the symbol "add" resides in the bytecode file index #45

Bytecode representation:
#45 add:
    // given the fact that the caller already pushed arguments unto the runtime stack
    CALL Integer::add()
    RET
*/

enum class Opcode {
    PUSH, // push a reference unto the runtime stack 
    POP,  // pop a reference from the runtime stack
    MOVE, // (MOVE a b) moves the owned reference from name a to name b
    COPY // (COPY a b) copy the borrowed/none reference from name a to name b
};

using Address = size_t;

class Function : public Object {
public:
    Function(Address __start__) : __start__(__start__) {}

    Reference* operator()(Runtime& rt) const {
        rt.pc = __start__;
    }
private:   
    Address __start__;
};

#endif