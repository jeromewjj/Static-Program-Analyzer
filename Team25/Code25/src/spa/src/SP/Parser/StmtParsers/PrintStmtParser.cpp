#include "PrintStmtParser.h"

#include "SP/Parser/ParserException.h"

shared_ptr<StatementNode> PrintStmtParser::parseStmt(Tokenizer& tokenizer) {
    Token variableToken = tokenizer.getNextToken();
    Token semicolonToken = tokenizer.getNextToken();

    if (variableToken.getType() != ALPHANUM and semicolonToken.getType() != SEMICOLON) {
        throw ParserException("Syntax Error: Invalid print Stmt");
    }

    auto printNode = std::make_shared<PrintNode>(variableToken.getValue(), stmtNum++);
    return printNode;
}
