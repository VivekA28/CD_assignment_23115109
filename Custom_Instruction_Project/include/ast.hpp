#pragma once
#include <string>
#include <memory>
#include <vector>

using namespace std; 

enum class NodeType {
    NUMBER, VARIABLE, BINARY_OP, ASSIGNMENT, PRINT
};

struct ASTNode {
    virtual NodeType getType() const = 0;
    virtual ~ASTNode() = default;
};

struct NumberNode : ASTNode {
    int value;
    explicit NumberNode(int val) : value(val) {}
    NodeType getType() const override { return NodeType::NUMBER; }
};

struct VariableNode : ASTNode {
    string name;
    explicit VariableNode(const string& n) : name(n) {}
    NodeType getType() const override { return NodeType::VARIABLE; }
};

struct BinaryOpNode : ASTNode {
    char op;
    shared_ptr<ASTNode> left;
    shared_ptr<ASTNode> right;

    BinaryOpNode(char o, shared_ptr<ASTNode> l, shared_ptr<ASTNode> r)
        : op(o), left(move(l)), right(move(r)) {}
    NodeType getType() const override { return NodeType::BINARY_OP; }
};

struct AssignmentNode : ASTNode {
    string varName;
    shared_ptr<ASTNode> expr;

    AssignmentNode(const string& var, shared_ptr<ASTNode> e)
        : varName(var), expr(move(e)) {}
    NodeType getType() const override { return NodeType::ASSIGNMENT; }
};

struct PrintNode : ASTNode {
    string varName;
    explicit PrintNode(const string& var) : varName(var) {}
    NodeType getType() const override { return NodeType::PRINT; }
};


