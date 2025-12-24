#ifndef COMPILE_LEXER_H
#define COMPILE_LEXER_H

#include <iostream>
#include <vector>
#include <cstring>
#include "compile/exceptions/lexer_exception.h"

enum class TokenKind {
    // keywords (for now)
    MODULE, FUNCTION, RETURN, CLASS, IF, ELSE, ENUM, IMPORT, WHILE, FOR, IN, CONTINUE, BREAK,

    // operators
    PLUS, MINUS, DIV, MOD, AMPERSAND,

    // symbols
    BINDER, // :=
    EQUALS, DOUBLE_EQUALS, BANG, BANG_EQUALS, SEMI_COLON, OPEN_CURLY, CLOSE_CURLY, OPEN_PAREN, CLOSE_PAREN, 
    COLON, DOUBLE_COLON,

    // ident 
    IDENT,
    

    // others
    HASH_TAG, // for comments
    EOL // End-of-line
};


struct Token {
    TokenKind kind;
    std::string lexeme;
    size_t line_no; // the line number this Token was generated from
    size_t char_start; // the index of the first character of this token

    Token(TokenKind kind, const std::string& lexeme, size_t line_no, size_t char_start) : kind(kind), lexeme(lexeme), line_no(line_no), char_start(char_start) {}
};

class Lexer {
public:
    Lexer() : walker(0), line_no(0) {}
    ~Lexer() = default;

    void parseLine(const std::string& line) {
        if (line.size() == 0) return;
        while (walker < line.size()) {
            auto ch = line[walker];
            switch (ch) {
                case '+':
                    tokens.push_back(Token(TokenKind::PLUS, "+", line_no, walker));
                    break;
                case '-':
                    tokens.push_back(Token(TokenKind::MINUS, "-", line_no, walker));
                    break;
                case '/':
                    tokens.push_back(Token(TokenKind::DIV, "/", line_no, walker));
                    break;
                case '&':
                    tokens.push_back(Token(TokenKind::AMPERSAND, "&", line_no, walker));
                case '\n':
                    tokens.push_back(Token(TokenKind::EOL, "\n", line_no, walker));
                    line_no++;
                    walker = 0;
                    return;
                case ':':
                    if (checkNext(line, ':')) {
                        tokens.push_back(Token(TokenKind::DOUBLE_COLON, "::", line_no, walker));
                    } else {
                        tokens.push_back(Token(TokenKind::COLON, ":", line_no, walker));
                    }
                    break;
                case '=':
                    if (checkNext(line, '=')) {
                        tokens.push_back(Token(TokenKind::DOUBLE_EQUALS, "==", line_no, walker));
                    } else {
                        tokens.push_back(Token(TokenKind::EQUALS, "=", line_no, walker));
                    }
                    break;
                case 
            }
            walker++; // advance the walker to the next character in the source stream
        }
    }

    // checks if the next character in line is tk
    bool checkNext(const std::string& line, char tk) {
        if (walker + 1 >= line.size()) throw LexerException("unable to scan next character in source stream");
        return line[walker + 1] == tk;
    }   

private:
    size_t walker;
    size_t line_no;
    std::vector<Token> tokens;
};

#endif