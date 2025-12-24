#ifndef RUNTIME_EXCEPTIONS_H
#define RUNTIME_EXCEPTIONS_H

#include <exception>
#include <string>

struct NullPointerException : public std::exception {
    std::string msg;

    NullPointerException(const std::string& msg) : msg(msg) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

struct AttributeException : std::exception {
     std::string msg;

    AttributeException(const std::string& msg) : msg(msg) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};


struct NameException : std::exception {
     std::string msg;

    NameException(const std::string& msg) : msg(msg) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

struct StackIndexException : std::exception {
     std::string msg;

    StackIndexException(const std::string& msg) : msg(msg) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

#endif