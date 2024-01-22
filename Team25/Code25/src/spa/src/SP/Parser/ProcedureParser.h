#pragma once
#include "../AST/ASTNode.h"
#include "../Tokenizer/Tokenizer.h"
using namespace std;

class ProcedureParser {
public:
    ProcedureParser();
    static ASTNodePtr parseProcedure(Tokenizer& tokenizer);

private:
    // validates proc declaration and returns proc name
    static string getProcedureName(Tokenizer& tokenizer);
};
