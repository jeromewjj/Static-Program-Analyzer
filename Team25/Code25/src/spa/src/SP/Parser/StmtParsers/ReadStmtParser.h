#pragma once

#include "SP/Parser/StmtParser.h"

class ReadStmtParser : public StmtParser {
public:
    shared_ptr<StatementNode> parseStmt(Tokenizer& tokenizer) override;
};