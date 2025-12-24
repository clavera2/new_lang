#ifndef COMPILE_EXCEPTION_LEXER_EXCEPTION_H
#define COMPILE_EXCEPTION_LEXER_EXCEPTION_H

#include <exception>
#include <string>

struct LexerException : public std::exception {
    std::string msg;

    LexerException(const std::string& msg) : msg(msg) {}

    const char *what() const noexcept override {
        return msg.c_str();
    }
};

#endif