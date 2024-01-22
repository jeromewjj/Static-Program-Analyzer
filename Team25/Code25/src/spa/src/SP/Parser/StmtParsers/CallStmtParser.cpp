#include "CallStmtParser.h"

#include "SP/AST/CallNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/Parser/ParserException.h"

shared_ptr<StatementNode> CallStmtParser::parseStmt(Tokenizer& tokenizer) {
    Token variableToken = tokenizer.getNextToken();
    Token semicolonToken = tokenizer.getNextToken();

    if (variableToken.getType() != ALPHANUM and semicolonToken.getType() != SEMICOLON) {
        throw ParserException("Syntax Error: Invalid Call Stmt");
    }

    auto callNode = std::make_shared<CallNode>(variableToken.getValue(), stmtNum++);
    return callNode;
}
