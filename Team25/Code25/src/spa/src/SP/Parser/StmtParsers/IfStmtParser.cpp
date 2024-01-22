#include "IfStmtParser.h"

#include "SP/AST/IfThenElseNode.h"
#include "SP/Parser/ParserException.h"
#include "SP/Parser/StmtLstParser.h"
#include "SP/Parser/StmtParsers/ExpressionParsers/ConditionalExpressionParser.h"
#include "SP/Parser/StmtTypes.h"

shared_ptr<StatementNode> IfStmtParser::parseStmt(Tokenizer& tokenizer) {
    auto ifNode = std::make_shared<IfThenElseNode>(stmtNum++);

    if (tokenizer.getNextToken().getType() != LEFT_PARENTHESIS) {
        throw ParserException("Syntax Error in IfStmtParser.cpp: Missing open bracket in if statement");
    }

    // Add conditional expression to left child
    shared_ptr<vector<Token>> expressionTokens = extractExpression(tokenizer);
    ConditionalExpressionParser expressionParser = ConditionalExpressionParser();
    std::shared_ptr<Expression> expressionNode = expressionParser.parseExpression(expressionTokens);
    ifNode->addChild(expressionNode);

    // Add first stmtLst to middle child
    ASTNodePtr stmtLstNode1 = StmtLstParser::parseStmtLst(tokenizer);
    ifNode->addChild(stmtLstNode1);

    Token closingCurlyToken = tokenizer.getNextToken();
    Token elseToken = tokenizer.getNextToken();
    Token openCurlyToken = tokenizer.getNextToken();

    if (closingCurlyToken.getType() != RIGHT_CURLY or
        (elseToken.getType() != ALPHANUM and elseToken.getValue() != StatementTypes::ELSE) or
        openCurlyToken.getType() != LEFT_CURLY) {
        throw ParserException("Syntax Error in IfStmtParser.cpp: Invalid else declaration");
    }

    // Add second stmtLst to last child
    ASTNodePtr stmtLstNode2 = StmtLstParser::parseStmtLst(tokenizer);
    ifNode->addChild(stmtLstNode2);

    if (tokenizer.getNextToken().getType() != RIGHT_CURLY) {
        throw ParserException("Syntax Error in IfStmtParser.cpp: Missing closing bracket in if statement");
    }

    return ifNode;
}

shared_ptr<vector<Token>> IfStmtParser::extractExpression(Tokenizer& tokenizer) {
    shared_ptr<vector<Token>> expressionTokens = make_shared<vector<Token>>();
    while (true) {
        Token currToken = tokenizer.getNextToken();
        if (currToken.getType() == LEFT_CURLY) {
            break;
        }
        if (currToken.getType() == EMPTY) {
            throw ParserException("Syntax Error: invalid if statement");
        }
        expressionTokens->push_back(currToken);
    }
    if (expressionTokens->empty()) {
        throw ParserException("Syntax Error: Empty if expression");
    }
    // Ensure last token is a 'then' declaration' and then remove it
    if (expressionTokens->back().getType() != ALPHANUM and
        expressionTokens->back().getValue() != StatementTypes::THEN) {
        throw ParserException("Syntax Error: Missing then declaration in if statement");
    }
    expressionTokens->pop_back();

    // Ensure second last token is a closing parenthesis and then remove it
    if (expressionTokens->back().getType() != RIGHT_PARENTHESIS) {
        throw ParserException("Syntax Error: Missing close bracket in if statement");
    }
    expressionTokens->pop_back();

    return expressionTokens;
}