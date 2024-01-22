#include "WhileStmtParser.h"

#include "SP/AST/WhileThenNode.h"
#include "SP/Parser/ParserException.h"
#include "SP/Parser/StmtLstParser.h"
#include "SP/Parser/StmtParsers/ExpressionParsers/ConditionalExpressionParser.h"

shared_ptr<StatementNode> WhileStmtParser::parseStmt(Tokenizer& tokenizer) {
    auto whileNode = std::make_shared<WhileThenNode>(stmtNum++);

    if (tokenizer.getNextToken().getType() != LEFT_PARENTHESIS) {
        throw ParserException("Syntax Error in WhileStmtParser.cpp: Missing open bracket in while statement");
    }

    // Add conditional expression to left child
    shared_ptr<vector<Token>> expressionTokens = extractExpression(tokenizer);
    ConditionalExpressionParser expressionParser = ConditionalExpressionParser(); // make this static?
    std::shared_ptr<Expression> expressionNode = expressionParser.parseExpression(expressionTokens);
    whileNode->addChild(expressionNode);

    // Add stmt lst to right child
    ASTNodePtr stmtLstNode = StmtLstParser::parseStmtLst(tokenizer);
    whileNode->addChild(stmtLstNode);

    if (tokenizer.getNextToken().getType() != RIGHT_CURLY) {
        throw ParserException("Syntax Error in WhileStmtParser.cpp: Missing closing bracket in while statement");
    }
    return whileNode;
}

shared_ptr<vector<Token>> WhileStmtParser::extractExpression(Tokenizer& tokenizer) {
    shared_ptr<vector<Token>> expressionTokens = make_shared<vector<Token>>();
    while (true) {
        Token currToken = tokenizer.getNextToken();
        if (currToken.getType() == LEFT_CURLY) {
            break;
        }
        if (currToken.getType() == EMPTY) {
            throw ParserException("Syntax Error: invalid while statement");
        }
        expressionTokens->push_back(currToken);
    }
    if (expressionTokens->empty()) {
        throw ParserException("Syntax Error: Empty while expression");
    }
    // Ensure last token is a closing parenthesis and then remove it
    if (expressionTokens->back().getType() != RIGHT_PARENTHESIS) {
        throw ParserException("Syntax Error: Missing close bracket in while statement");
    }
    expressionTokens->pop_back();

    return expressionTokens;
}
