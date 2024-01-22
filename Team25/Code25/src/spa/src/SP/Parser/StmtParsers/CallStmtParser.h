#pragma once

#include "SP/Parser/StmtParser.h"

class CallStmtParser : public StmtParser {
public:
    shared_ptr<StatementNode> parseStmt(Tokenizer& tokenizer) override;
};