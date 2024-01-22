#pragma once
#include "../AST/ASTNode.h"
#include "../Tokenizer/Tokenizer.h"
using namespace std;

class Parser {
public:
    Parser(Tokenizer& tokenizer);
    ~Parser();
    ASTNodePtr parseProgram();

private:
    Tokenizer tokenizer;
};