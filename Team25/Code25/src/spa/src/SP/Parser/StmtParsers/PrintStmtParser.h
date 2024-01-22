#pragma once

#include "SP/AST/PrintNode.h"
#include "SP/Parser/StmtParser.h"

class PrintStmtParser : public StmtParser {
public:
    shared_ptr<StatementNode> parseStmt(Tokenizer& tokenizer) override;
};