#include "../include/parser.hpp"
#include <stdexcept>

using namespace std;

Parser::Parser(const vector<Token>& t) : tokens(t), pos(0) {}

Token Parser::peek() {
    return pos < tokens.size() ? tokens[pos] : Token{TokenType::END, ""};
}

Token Parser::advance() {
    return pos < tokens.size() ? tokens[pos++] : Token{TokenType::END, ""};
}

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

vector<shared_ptr<ASTNode>> Parser::parse() {
    vector<shared_ptr<ASTNode>> program;
    while (peek().type != TokenType::END) {
        program.push_back(parseStatement());
    }
    return program;
}

shared_ptr<ASTNode> Parser::parseStatement() {
    if (match(TokenType::INT)) {
        if (peek().type != TokenType::ID)
            throw runtime_error("Expected identifier after 'int'");
        string name = advance().value;

        if (!match(TokenType::ASSIGN))
            throw runtime_error("Expected '='");
        
        auto expr = parseExpression();
        if (!match(TokenType::SEMICOLON))
            throw runtime_error("Expected ';'");
        
        return make_shared<AssignmentNode>(name, expr);
    }

    if (match(TokenType::PRINT)) {
        if (!match(TokenType::LPAREN))
            throw runtime_error("Expected '(' after print");
        
        if (peek().type != TokenType::ID)
            throw runtime_error("Expected identifier inside print");
        string var = advance().value;

        if (!match(TokenType::RPAREN))
            throw runtime_error("Expected ')'");
        if (!match(TokenType::SEMICOLON))
            throw runtime_error("Expected ';'");
        
        return make_shared<PrintNode>(var);
    }

    throw runtime_error("Invalid statement");
}

shared_ptr<ASTNode> Parser::parseExpression() {
    auto node = parseTerm();
    while (peek().type == TokenType::ADD || peek().type == TokenType::SUB) {
        char op = advance().value[0];
        auto right = parseTerm();
        node = make_shared<BinaryOpNode>(op, node, right);
    }
    return node;
}

shared_ptr<ASTNode> Parser::parseTerm() {
    auto node = parseFactor();
    while (peek().type == TokenType::MUL) {
        char op = advance().value[0];
        auto right = parseFactor();
        node = make_shared<BinaryOpNode>(op, node, right);
    }
    return node;
}

shared_ptr<ASTNode> Parser::parseFactor() {
    Token token = advance();
    if (token.type == TokenType::NUMBER) {
        return make_shared<NumberNode>(stoi(token.value));
    } else if (token.type == TokenType::ID) {
        return make_shared<VariableNode>(token.value);
    } else if (token.type == TokenType::LPAREN) {
        auto expr = parseExpression();
        if (!match(TokenType::RPAREN))
            throw runtime_error("Expected ')'");
        return expr;
    }

    throw runtime_error("Unexpected token in expression");
}
