#ifndef RUNTIME_TYPES_H
#define RUNTIME_TYPES_H

#include <string>
#include "reference.h"
#include <vector>

struct Frame {
    std::vector<Reference *> st_frame;

    Frame(const std::vector<Reference *>& fr) : st_frame(fr) {}
    ~Frame() = default;

    Reference* operator[](size_t idx) {
        if (idx >= st_frame.size()) throw StackIndexException("invalid stack frame index access");
        return st_frame[idx];
    }

    void push(Reference* r) {
        st_frame.push_back(r);
    }
};

enum class FunctionType {
    FREE, 
    INSTANCE,
    STATIC
};

// base class for all function types
class Function {
public:
    Function(const std::string& name, FunctionType type);
    virtual ~Function() = default;
    virtual FunctionType getType() const = 0;
    virtual bool isInstanceMethod() const = 0;
    virtual bool isStaticMethod() const = 0;
    virtual bool isFreeFunction() const = 0;
protected:
    std::string name;
    FunctionType type;
};

// represents a function that is dependent on an instance of a class
class InstanceMethod {

};

class StaticMethod {

};

#endif