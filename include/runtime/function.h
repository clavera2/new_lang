#ifndef RUNTIME_TYPES_H
#define RUNTIME_TYPES_H

#include "./namespace.h"
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

class Instruction {
public:
    static Instruction makeUnary(Opcode op) {
        // dummy impl for now
        switch (op) {
            case Opcode::PUSH:
                return Instruction(Opcode::PUSH);
        }
        return Instruction(Opcode::PUSH);
    }
private:
    Opcode opcode;
    std::optional<std::vector<std::string>> operands;
    Instruction(Opcode opcode,  std::optional<std::vector<std::string>> operands = std::nullopt) : opcode(opcode), operands(operands) {}
};

using Address = size_t; // represents an index in a bytecode file

/* 
represents a sequence of bytecode with addresses in the format #ADDRESS BYTE_CODE
e.g: #1 PUSH 1
     #2 PUSH 2
     #3 ADD
     #4 RET
*/
class code_object {
public:
    code_object();
    ~code_object() = default;
private:
    friend class Runtime;
    friend class Function;
    Address _start; // the starting address of the code object
    std::unordered_map<Address, Instruction> instructions;
};

class Function : public NameSpace {
public:
    Function(const std::string& name, size_t arg_size) : name(name), arg_size(arg_size) {}

    // sets the runtime pc to this->pc
    void call(Runtime& rt) {
        rt.pc = _code._start;
    }

    const std::string& getName() const { return name; }
private:
    std::string name;
    size_t arg_size;
    code_object _code;
};

#endif