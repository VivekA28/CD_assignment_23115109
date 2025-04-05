#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast.hpp"
#include <unordered_map>
#include <string>   

class Interpreter {
private:
    std::unordered_map<std::string, int> variables;

public:
    void evaluate(ASTNode* node);

private:
    int evalExpr(ASTNode* node);
};

#endif // INTERPRETER_HPP
