#ifndef RUNTIME_RT_H
#define RUNTIME_RT_H

#include <cstddef>
#include <stack>
#include "./function.h"
#include "./globals.h"

#define MAX_STACK_SIZE 1024// to be determined

using Address = size_t;

constexpr Address END_ADDRESS = -1;

enum class Opcode {

};

struct Instruction {
    Opcode op;
    size_t operand; // address, symbol index, etc.
};

struct Frame {
    Address returnAddress;
    size_t base;
};



class Runtime {
public:
    Runtime(const std::vector<Instruction>& code) : ip(0), code(code) {}

    void push(Reference* ref) {
        valueStack.push_back(ref);
    }

    Reference* pop() {
        auto* r = valueStack.back();
        valueStack.pop_back();
        return r;
    }

    Reference* peek() {
        return valueStack.back();
    }

     void pushFrame(Address entry, size_t arity) {
        Frame frame;
        frame.returnAddress = ip;
        frame.base = valueStack.size() - arity;

        callStack.push(frame);
        ip = entry;
    }

    void popFrame() {
        auto frame = callStack.top();
        callStack.pop();

        Reference* ret = pop();
        valueStack.resize(frame.base);

        push(ret);
        ip = frame.returnAddress;
    }

    // starts the VM
    void run() {
        initGlobals();
        while (ip != END_ADDRESS) {
            // FDE cycle continuously runs until pc == END_ADDRESS
            const Instruction& instruction = code[ip++];
        }
    }

    void pushStackFrame(Address ret, size_t arity) {

    }
private:
    Reference* resolveFunction(size_t symbol);

private:
    const std::vector<Instruction>& code;
    Address ip;

    std::vector<Reference*> valueStack;
    std::stack<Frame> callStack;
};

#endif