#pragma once
#include <fstream>
#include <string>
#include "ast.hpp"

class CodeGenerator {
public:
    explicit CodeGenerator(const std::string& filename);
    ~CodeGenerator();
    void generate(std::shared_ptr<ASTNode> node);

private:
    std::ofstream asmFile;
    void handleAssignment(AssignmentNode* assign);
    bool isSquareDiff(BinaryOpNode* bin);
    std::string getExpr(ASTNode* node);
};
