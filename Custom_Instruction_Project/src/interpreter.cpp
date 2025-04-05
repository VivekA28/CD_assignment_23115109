#include "../include/interpreter.hpp"
#include <iostream>

using namespace std;

void Interpreter::evaluate(ASTNode* node) {
    if (!node) return;

    if (auto assign = dynamic_cast<AssignmentNode*>(node)) {
        int value = evalExpr(assign->expr.get());
        variables[assign->varName] = value;
    } else if (auto printNode = dynamic_cast<PrintNode*>(node)) {
        auto it = variables.find(printNode->varName);
        if (it != variables.end()) {
            cout << it->second << endl;
        } else {
            cerr << "Error: Undefined variable '" << printNode->varName << "'" << endl;
        }
    }
}

int Interpreter::evalExpr(ASTNode* node) {
    if (auto num = dynamic_cast<NumberNode*>(node)) return num->value;
    if (auto var = dynamic_cast<VariableNode*>(node)) return variables[var->name];
    if (auto bin = dynamic_cast<BinaryOpNode*>(node)) {
        int left = evalExpr(bin->left.get());
        int right = evalExpr(bin->right.get());
        switch (bin->op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return right != 0 ? left / right : 0;
        }
    }
    return 0;
}
