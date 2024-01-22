#pragma once
#include "../Tokenizer/Tokenizer.h"
#include "SP/AST/StmtListNode.h"
#include "StmtParser.h"

class StmtLstParser {
public:
    static std::shared_ptr<StmtListNode> parseStmtLst(Tokenizer& tokenizer);

private:
    static std::unique_ptr<StmtParser> IdentifyStmtParser(const Token& currToken, const Token& nextToken);
};
