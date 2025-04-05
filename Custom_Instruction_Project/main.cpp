#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.hpp"
#include "parser.hpp"
#include "codegen.hpp"
#include "interpreter.hpp"

using namespace std;

ostream& operator<<(ostream& os, const TokenType& type) {
    switch (type) {
        case TokenType::INT:        return os << "INT";
        case TokenType::ID:         return os << "ID";
        case TokenType::NUMBER:     return os << "NUMBER";
        case TokenType::ASSIGN:     return os << "ASSIGN";
        case TokenType::ADD:        return os << "ADD";
        case TokenType::SUB:        return os << "SUB";
        case TokenType::MUL:        return os << "MUL";
        case TokenType::DIV:        return os << "DIV";
        case TokenType::PRINT:      return os << "PRINT";
        case TokenType::LPAREN:     return os << "LPAREN";
        case TokenType::RPAREN:     return os << "RPAREN";
        case TokenType::SEMICOLON:  return os << "SEMICOLON";
        case TokenType::END:        return os << "END";
        default:                    return os << "UNKNOWN";
    }
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cerr << "Error: input.txt not found." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string sourceCode = buffer.str();

    cout << "<--- Tokenisation --->" << endl;
    Lexer lexer(sourceCode);
    vector<Token> tokens = lexer.tokenize();
    for (auto& tok : tokens) {
        cout << "(" << tok.type << ", " << tok.value << ")" << endl;
    }

    cout << "\n<--- Parsing --->" << endl;
    Parser parser(tokens);
    vector<shared_ptr<ASTNode>> statements = parser.parse();  

    cout << "\n<--- Code Generation --->" << endl;
    CodeGenerator gen("output.asm");
    for (auto& stmt : statements) {
        gen.generate(stmt);  
    }

    cout << "\n Assembly code written to output.asm" << endl;

    cout << "\n<--- Interpreting Result(s) --->" << endl;
    Interpreter interpreter;
    for (auto& stmt : statements) {
        interpreter.evaluate(stmt.get());
    }

    return 0;
}
