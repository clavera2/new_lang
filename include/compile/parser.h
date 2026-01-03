#ifndef COMPILE_PARSER_H
#define COMPILE_PARSER_H

#include "./lexer.h"
#include <vector>

struct TokenStream {
    std::vector<Token> tokens;
    size_t walker;
    
    TokenStream(const std::vector<Token>& tokens) : tokens(tokens), walker(0) {}

    void reset() { 
        walker = 0;
    }

    // checks the stream if the next token is of type kind
    bool checkNext(TokenKind kind) {
        return tokens[walker + 1].kind == kind;
    }

    // gets the current token, progressing the walker
    Token get() {
        Token tk = tokens[walker];
        walker++;
    }
};

class Parser {  
public:
private:

};

#endif