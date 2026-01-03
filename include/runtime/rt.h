#ifndef RUNTIME_RT_H
#define RUNTIME_RT_H

#include <cstddef>
#include <stack>
#include "./function.h"
#include "./globals.h"

#define MAX_STACK_SIZE 1024// to be determined

using Address = size_t;

constexpr Address END_ADDRESS = -1;

class Runtime {
public:
    Runtime() : pc(0), stack() {}

    void push(Reference* ref) {
        if (stack.size() == MAX_STACK_SIZE) throw ("stack overflow exception");
        stack.push(ref);
    }

    Reference* pop() {
        if (stack.size() == 0) throw StackUnderflowException("stack underflow exception");
        auto r = stack.top();
        stack.pop();
        return r;
    }

    void clear() {
        while (! stack.empty()) {
            Reference* r = pop();
            delete r;
        }
    }

    // starts the VM
    void run() {
        initGlobals();
        while (pc != END_ADDRESS) {
            
            pc++;
        }
    }
private:
    friend class Function;
    Address pc;
    std::stack<Reference*> stack;
};

#endif