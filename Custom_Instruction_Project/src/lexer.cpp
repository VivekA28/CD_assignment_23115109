// src/lexer.cpp
#include "../include/lexer.hpp"
#include <cctype>

using namespace std;

Lexer::Lexer(const string& src) : source(src), pos(0) {}

char Lexer::peek() {
    if (pos >= source.length()) return '\0';
    return source[pos];
}

char Lexer::advance() {
    return pos < source.length() ? source[pos++] : '\0';
}

void Lexer::skipWhitespace() {
    while (isspace(peek())) advance();
}

Token Lexer::identifier() {
    string value;
    while (isalnum(peek()) || peek() == '_') value += advance();

    if (value == "int") return {TokenType::INT, value};
    if (value == "print") return {TokenType::PRINT, value};
    return {TokenType::ID, value};
}

Token Lexer::number() {
    string value;
    while (isdigit(peek())) value += advance();
    return {TokenType::NUMBER, value};
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;

    while (peek() != '\0') {
        skipWhitespace();
        char current = peek();

        if (isalpha(current)) {
            tokens.push_back(identifier());
        } else if (isdigit(current)) {
            tokens.push_back(number());
        } else {
            switch (current) {
                case '=': tokens.push_back({TokenType::ASSIGN, "="}); break;
                case '*': tokens.push_back({TokenType::MUL, "*"}); break;
                case '-': tokens.push_back({TokenType::SUB, "-"}); break;
                case '+': tokens.push_back({TokenType::ADD, "+"}); break;
                case ';': tokens.push_back({TokenType::SEMICOLON, ";"}); break;
                case '(': tokens.push_back({TokenType::LPAREN, "("}); break;
                case ')': tokens.push_back({TokenType::RPAREN, ")"}); break;
                default: break;
            }
            advance();
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}
