// include/parser.hpp
#pragma once

#include <memory>
#include <vector>
#include "ast.hpp"
#include "lexer.hpp"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::vector<std::shared_ptr<ASTNode>> parse();

private:
    const std::vector<Token>& tokens;
    size_t pos;

    Token peek();
    Token advance();
    bool match(TokenType type);

    std::shared_ptr<ASTNode> parseStatement();
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();
};

