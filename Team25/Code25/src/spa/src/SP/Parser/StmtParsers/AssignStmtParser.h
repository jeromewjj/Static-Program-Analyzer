#pragma once

#include "SP/Parser/StmtParser.h"

class AssignStmtParser : public StmtParser {
public:
    shared_ptr<StatementNode> parseStmt(Tokenizer& tokenizer) override;

private:
    shared_ptr<vector<Token>> extractExpression(Tokenizer& tokenizer);
};