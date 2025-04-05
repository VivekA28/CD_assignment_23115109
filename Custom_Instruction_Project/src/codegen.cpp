#include "../include/codegen.hpp"
#include <iostream>

CodeGenerator::CodeGenerator(const std::string& filename) {
    asmFile.open(filename);
    if (!asmFile.is_open()) {
        std::cerr << "Failed to open output file.\n";
    }
}

CodeGenerator::~CodeGenerator() {
    if (asmFile.is_open()) {
        asmFile.close();
    }
}

void CodeGenerator::generate(std::shared_ptr<ASTNode> node) {
    if (auto assign = dynamic_pointer_cast<AssignmentNode>(node)) {
        handleAssignment(assign.get());
    } else if (auto printNode = dynamic_pointer_cast<PrintNode>(node)) {
        asmFile << "PRINT " << printNode->varName << "\n";
    }
}

void CodeGenerator::handleAssignment(AssignmentNode* assign) {
    auto expr = assign->expr.get();

    if (auto bin = dynamic_cast<BinaryOpNode*>(expr)) {
        if (isSquareDiff(bin)) {
            std::string leftVar = getExpr(bin->left.get());
            std::string rightVar = getExpr(bin->right.get());
            asmFile << "SQUAREDIFF " << assign->varName << ", " << leftVar << ", " << rightVar << "\n";
            return;
        }
    }

    asmFile << assign->varName << " = " << getExpr(expr) << "\n";
}

bool CodeGenerator::isSquareDiff(BinaryOpNode* bin) {
    if (bin->op != '-') return false;

    auto left = dynamic_cast<BinaryOpNode*>(bin->left.get());
    auto right = dynamic_cast<BinaryOpNode*>(bin->right.get());

    if (!left || !right) return false;

    auto lvar1 = dynamic_cast<VariableNode*>(left->left.get());
    auto lvar2 = dynamic_cast<VariableNode*>(left->right.get());

    auto rvar1 = dynamic_cast<VariableNode*>(right->left.get());
    auto rvar2 = dynamic_cast<VariableNode*>(right->right.get());

    return left->op == '*' && right->op == '*' &&
           lvar1 && lvar2 && rvar1 && rvar2 &&
           lvar1->name == lvar2->name &&
           rvar1->name == rvar2->name;
}

std::string CodeGenerator::getExpr(ASTNode* node) {
    if (auto num = dynamic_cast<NumberNode*>(node)) return std::to_string(num->value);
    if (auto var = dynamic_cast<VariableNode*>(node)) return var->name;
    if (auto bin = dynamic_cast<BinaryOpNode*>(node)) {
        return "(" + getExpr(bin->left.get()) + " " + bin->op + " " + getExpr(bin->right.get()) + ")";
    }
    return "";
}
