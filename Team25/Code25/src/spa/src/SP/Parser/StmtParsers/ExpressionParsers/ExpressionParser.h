#pragma once
#include "SP/AST/ASTNode.h"
#include "SP/AST/BinaryExpressionNode.h"
#include "SP/AST/Expression.h"
#include "SP/Tokenizer/Tokenizer.h"
#include "stack"

class ExpressionParser {
public:
    std::shared_ptr<Expression> parseExpression(const shared_ptr<vector<Token>>& infixTokens);

private:
    shared_ptr<vector<Token>> infixToPostfix(const shared_ptr<vector<Token>>& infixTokens);

    virtual std::shared_ptr<Expression> postFixToTree(const shared_ptr<vector<Token>>& postFixTokens) = 0;

    virtual int precedence(TokenType type) = 0;

    virtual string& identifyOperatorType(Token& token) = 0;

    virtual bool isValidTokenType(Token& token) = 0;

    virtual void validateExpression(const shared_ptr<vector<Token>>& infixTokens) = 0;

    void isTerm(const shared_ptr<vector<Token>>& infixTokens, size_t start, size_t end);

    void isFactor(const shared_ptr<vector<Token>>& infixTokens, size_t start, size_t end);

protected:
    void isAssignmentExpr(const shared_ptr<vector<Token>>& infixTokens, size_t start, size_t end);
};
