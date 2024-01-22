#include "AssignStmtParser.h"

#include "SP/AST/AssignNode.h"
#include "SP/Parser/ParserException.h"
#include "SP/Parser/StmtParsers/ExpressionParsers/AssignmentExpressionParser.h"

shared_ptr<StatementNode> AssignStmtParser::parseStmt(Tokenizer& tokenizer) {
    // Check that assignment begins with variable and single equal sign
    Token variableToken = tokenizer.getCurrToken();
    Token equalToken = tokenizer.getNextToken();

    if (variableToken.getType() != ALPHANUM or equalToken.getType() != SINGLE_EQUAL) {
        throw ParserException("Syntax Error: Invalid assign Stmt");
    }

    // Add variable as left child of assignment node
    auto assignNode = std::make_shared<AssignNode>(variableToken.getValue(), stmtNum++);

    // Generate expression and append to right of assignment node
    shared_ptr<vector<Token>> expressionTokens = extractExpression(tokenizer);
    AssignmentExpressionParser expressionParser = AssignmentExpressionParser(); // make this static?
    std::shared_ptr<Expression> expressionNode = expressionParser.parseExpression(expressionTokens);
    assignNode->addChild(expressionNode);

    return assignNode;
}

shared_ptr<vector<Token>> AssignStmtParser::extractExpression(Tokenizer& tokenizer) {
    shared_ptr<vector<Token>> expressionTokens = make_shared<vector<Token>>();
    while (true) {
        Token currToken = tokenizer.getNextToken();
        if (currToken.getType() == SEMICOLON) {
            break;
        }
        if (currToken.getType() == EMPTY) {
            throw ParserException("Syntax Error: Missing semi-colon in assign Stmt");
        }
        expressionTokens->push_back(currToken);
    }
    return expressionTokens;
}
