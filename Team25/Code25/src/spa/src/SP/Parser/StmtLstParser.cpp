#include "StmtLstParser.h"

#include "ParserException.h"
#include "SP/AST/StmtListNode.h"
#include "StmtParsers/AssignStmtParser.h"
#include "StmtParsers/CallStmtParser.h"
#include "StmtParsers/IfStmtParser.h"
#include "StmtParsers/PrintStmtParser.h"
#include "StmtParsers/ReadStmtParser.h"
#include "StmtParsers/WhileStmtParser.h"
#include "StmtTypes.h"

// Method is called when open curly bracket is the curr token being pointed at
std::shared_ptr<StmtListNode> StmtLstParser::parseStmtLst(Tokenizer& tokenizer) {
    auto stmtListNode = std::make_shared<StmtListNode>();
    bool isChildPresent = false;

    // parse statements within stmtList
    // stop when there is a closing bracket that indicates end of stmtList
    while (tokenizer.peekNextToken().getType() != RIGHT_CURLY) {
        Token currToken = tokenizer.getNextToken();
        Token nextToken = tokenizer.peekNextToken();

        // When one of the stmt parsers are called, the pointer will be at the first token of the stmt
        std::unique_ptr<StmtParser> stmtParser = IdentifyStmtParser(currToken, nextToken);
        shared_ptr<StatementNode> childNode = stmtParser->parseStmt(tokenizer);
        stmtListNode->addChild(childNode);
        isChildPresent = true;
    }
    if (!isChildPresent) {
        throw ParserException("Empty stmt lst");
    }
    return stmtListNode;
}

std::unique_ptr<StmtParser> StmtLstParser::IdentifyStmtParser(const Token& currToken, const Token& nextToken) {
    string stmtValue = currToken.getValue();

    if (nextToken.getType() == SINGLE_EQUAL) {
        return std::make_unique<AssignStmtParser>();
    }
    if (stmtValue == StatementTypes::READ) {
        return std::make_unique<ReadStmtParser>();
    }
    if (stmtValue == StatementTypes::PRINT) {
        return std::make_unique<PrintStmtParser>();
    }
    if (stmtValue == StatementTypes::CALL) {
        return std::make_unique<CallStmtParser>();
    }
    if (stmtValue == StatementTypes::WHILE) {
        return std::make_unique<WhileStmtParser>();
    }
    if (stmtValue == StatementTypes::IF) {
        return std::make_unique<IfStmtParser>();
    }

    throw ParserException("Invalid stmt entity: " + stmtValue);
}