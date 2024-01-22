#pragma once
#include <string>

#include "../AST/ASTNode.h"
#include "../Tokenizer/Tokenizer.h"
#include "SP/AST/StatementNode.h"

class StmtParser {
public:
    virtual ~StmtParser() = default;
    virtual shared_ptr<StatementNode> parseStmt(Tokenizer& tokenizer) = 0;
    static void resetStmtNum();

protected:
    static int stmtNum;
};
