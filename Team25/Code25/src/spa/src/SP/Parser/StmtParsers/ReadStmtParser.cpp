#include "ReadStmtParser.h"

#include "../ParserException.h"
#include "SP/AST/ReadNode.h"

shared_ptr<StatementNode> ReadStmtParser::parseStmt(Tokenizer& tokenizer) {
    Token variableToken = tokenizer.getNextToken();
    Token semicolonToken = tokenizer.getNextToken();

    if (variableToken.getType() != ALPHANUM and semicolonToken.getType() != SEMICOLON) {
        throw ParserException("Invalid Read Stmt");
    }

    auto readNode = std::make_shared<ReadNode>(variableToken.getValue(), stmtNum++);
    return readNode;
}