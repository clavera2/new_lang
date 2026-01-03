#ifndef COMPILE_LEXER_H
#define COMPILE_LEXER_H

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <unordered_map>
#include "compile/exceptions/lexer_exception.h"

enum class TokenKind {
    // keywords (for now)
    MODULE, FUNCTION, RETURN, CLASS, IF, ELSE, ENUM, IMPORT, WHILE, FOR, IN, CONTINUE, BREAK,

    // operators
    PLUS, MINUS, DIV, MOD, AMPERSAND,

    // symbols
    BINDER, // :=
    EQUALS, DOUBLE_EQUALS, BANG, BANG_EQUALS, SEMI_COLON, OPEN_CURLY, CLOSE_CURLY, OPEN_PAREN, CLOSE_PAREN, 
    COLON, DOUBLE_COLON, QUESTION_MARK,

    // ident 
    IDENT,
    

    // others
    HASH_TAG, // for comments
    EOL // End-of-line
};


static const std::unordered_map<std::string, TokenKind> keywords = {
    {"module", TokenKind::MODULE},
    {"function", TokenKind::FUNCTION},
    {"return", TokenKind::RETURN},
    {"class", TokenKind::CLASS},
    {"if", TokenKind::IF},
    {"else", TokenKind::ELSE},
    {"while", TokenKind::WHILE},
    {"for", TokenKind::FOR},
    {"break", TokenKind::BREAK},
    {"continue", TokenKind::CONTINUE}
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
    Lexer(const std::string& source) : source(source), walker(0), line_no(0) {}
    ~Lexer() = default;

    void parseAll() {
        std::ifstream file = std::ifstream(source);
        if (! file.is_open())  {
            std::cout << "error: could not open source file\n";
            std::exit(1);
        }

        std::string line;
        while (std::getline(file, line)) {
            parseLine(line);
            line_no++;
        }
    }

    void parseLine(const std::string& line) {
        walker = 0;
        if (line.size() == 0) return;
        while (walker < line.size()) {
            auto ch = line[walker];
            if (std::isalpha(ch) || ch == '_') {
                size_t start = walker;
                std::string ident;

                while (walker < line.size() &&
                    (std::isalnum(line[walker]) || line[walker] == '_')) {
                    ident += line[walker];
                    walker++;
                }

                auto it = keywords.find(ident);
                if (it != keywords.end()) {
                    tokens.emplace_back(it->second, ident, line_no, start);
                } else {
                    tokens.emplace_back(TokenKind::IDENT, ident, line_no, start);
                }

                continue; 
            } else {
            switch (ch) {
                case ' ':
                    break;
                case '{':
                    tokens.push_back(Token(TokenKind::OPEN_CURLY, "{", line_no, walker));
                    break;
                case '}':
                    tokens.push_back(Token(TokenKind::CLOSE_CURLY, "}", line_no, walker));
                    break;
                case '(':
                    tokens.push_back(Token(TokenKind::OPEN_PAREN, "(", line_no, walker));
                    break;
                case ')':
                    tokens.push_back(Token(TokenKind::CLOSE_PAREN, ")", line_no, walker));
                    break;
                case ';':
                    tokens.push_back(Token(TokenKind::SEMI_COLON, ";", line_no, walker));
                    break;
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
                    break;
                case '\n':
                    tokens.push_back(Token(TokenKind::EOL, "\n", line_no, walker));
                    line_no++;
                    walker = 0;
                    return;
                case ':':
                    if (checkNext(line, ':')) {
                        tokens.push_back(Token(TokenKind::DOUBLE_COLON, "::", line_no, walker));
                        walker++;
                    } else if (checkNext(line, '=')) {
                        tokens.push_back(Token(TokenKind::BINDER, ":=", line_no, walker));
                    } else {
                        tokens.push_back(Token(TokenKind::COLON, ":", line_no, walker));
                    }
                    break;
                case '=':
                    if (checkNext(line, '=')) {
                        tokens.push_back(Token(TokenKind::DOUBLE_EQUALS, "==", line_no, walker));
                        walker++;
                    } else {
                        tokens.push_back(Token(TokenKind::EQUALS, "=", line_no, walker));
                    }
                    break;
                case '?':
                    tokens.push_back(Token(TokenKind::QUESTION_MARK, "?", line_no, walker));
                    break;
                default:
                    throw LexerException("Unexpected character: " + std::string(1, ch));        
            }   
        }
              walker++; // advance the walker to the next character in the source stream
        }
    }

    // checks if the next character in line is tk
    bool checkNext(const std::string& line, char tk) {
        return walker + 1 < line.size() && line[walker + 1] == tk;
    }   

    void emit(TokenKind kind, const std::string& lexeme) {
        tokens.emplace_back(kind, lexeme, line_no, walker);
    }
private:
    size_t walker;
    size_t line_no;
    std::vector<Token> tokens;
    std::string source;
};

#endif