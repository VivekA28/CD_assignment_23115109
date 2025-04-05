// include/lexer.hpp
#pragma once
#include <string>
#include <vector>

using namespace std; 

enum class TokenType {
    INT, ID, ASSIGN, NUMBER, MUL, SUB, ADD,
    PRINT, LPAREN, RPAREN, SEMICOLON, END, DIV
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {
public:
    explicit Lexer(const string& src);
    vector<Token> tokenize();

private:
    string source;
    size_t pos;
    char peek();
    char advance();
    void skipWhitespace();
    Token identifier();
    Token number();
};
