#ifndef RUNTIME_TYPES_H
#define RUNTIME_TYPES_H

#include "./object.h"
#include "./rt.h"

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

using Address = size_t; // represents an index in a bytecode file

class Function : public Object {
public:
    Function(size_t arg_size, Address pc) : arg_size(arg_size), pc(pc) {}

    // sets the runtime pc to this->pc
    void call(Runtime& rt) {
        rt.pc = pc;
    }
private:
    size_t arg_size;
    Address pc;
};

#endif