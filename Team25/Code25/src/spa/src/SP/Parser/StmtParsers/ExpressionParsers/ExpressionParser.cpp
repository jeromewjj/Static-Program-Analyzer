#include "ExpressionParser.h"

#include "SP/AST/ConstantNode.h"
#include "SP/AST/VariableNode.h"
#include "SP/Parser/ParserException.h"

std::shared_ptr<Expression> ExpressionParser::parseExpression(const shared_ptr<vector<Token>>& infixTokens) {
    validateExpression(infixTokens);
    shared_ptr<vector<Token>> postFixTokens = infixToPostfix(infixTokens);
    std::shared_ptr<Expression> expressionNode = postFixToTree(postFixTokens);
    return expressionNode;
}

shared_ptr<vector<Token>> ExpressionParser::infixToPostfix(const shared_ptr<vector<Token>>& infixTokens) {
    stack<Token> operators;
    shared_ptr<vector<Token>> postfixTokens = make_shared<vector<Token>>();

    for (auto itr = infixTokens->begin(); itr != infixTokens->end(); itr++) {
        Token token = (*itr);
        TokenType tokenType = token.getType();

        if (tokenType == CONST or tokenType == ALPHANUM) {
            postfixTokens->push_back(token);
        }
        else if (tokenType == LEFT_PARENTHESIS) {
            operators.push(token);
        }
        else if (tokenType == RIGHT_PARENTHESIS) {
            // If token is a closing parenthesis, pop operators from the stack
            // and add them to the postfix expression until an opening parenthesis is encountered
            while (!operators.empty() && operators.top().getType() != TokenType::LEFT_PARENTHESIS) {
                postfixTokens->push_back(operators.top());
                operators.pop();
            }
            // Pop the opening parenthesis from the stack
            operators.pop();
        }
        else if (isValidTokenType(token)) {
            // If token is an operator, pop operators from the stack and add them to
            // the postfix expression as long as they have higher or equal precedence
            while (!operators.empty() && operators.top().getType() != TokenType::LEFT_PARENTHESIS &&
                   precedence(operators.top().getType()) >= precedence(token.getType())) {
                postfixTokens->push_back(operators.top());
                operators.pop();
            }
            // Push the current operator onto the stack
            operators.push(token);
        }
    }
    // Pop any remaining operators from the stack and add them to the postfix expression
    while (!operators.empty()) {
        postfixTokens->push_back(operators.top());
        operators.pop();
    }
    return postfixTokens;
}

void ExpressionParser::isAssignmentExpr(const shared_ptr<vector<Token>>& infixTokens, size_t start, size_t end) {
    if (start > end) {
        throw ParserException("Invalid expression: Expression not found");
    }
    // Parenthesis count is to ensure that the operator im at the right level
    int parenthesis_count = 0;

    for (size_t i = end; i > start; --i) {
        const Token& token = infixTokens->at(i);

        if (parenthesis_count == 0 && (token.getType() == PLUS || token.getType() == MINUS)) {
            isAssignmentExpr(infixTokens, start, i - 1);
            isTerm(infixTokens, i + 1, end);
            return;
        }
        else if (token.getType() == TokenType::LEFT_PARENTHESIS) {
            parenthesis_count++;
        }
        else if (token.getType() == TokenType::RIGHT_PARENTHESIS) {
            parenthesis_count--;
        }
    }
    isTerm(infixTokens, start, end);
}

void ExpressionParser::isTerm(const shared_ptr<vector<Token>>& infixTokens, size_t start, size_t end) {
    if (start > end) {
        throw ParserException("Invalid term in expression: Term not found");
    }

    int parenthesis_count = 0;
    for (size_t i = end; i > start; --i) {

        const Token& token = infixTokens->at(i);
        if (parenthesis_count == 0 &&
            (token.getType() == DIVIDE || token.getType() == MULTIPLY || token.getType() == MOD)) {
            isTerm(infixTokens, start, i - 1);
            isFactor(infixTokens, i + 1, end);
            return;
        }
        else if (token.getType() == TokenType::LEFT_PARENTHESIS) {
            parenthesis_count++;
        }
        else if (token.getType() == TokenType::RIGHT_PARENTHESIS) {
            parenthesis_count--;
        }
    }
    isFactor(infixTokens, start, end);
}

void ExpressionParser::isFactor(const shared_ptr<vector<Token>>& infixTokens, size_t start, size_t end) {
    const Token& startToken = (*infixTokens)[start];
    const Token& endToken = (*infixTokens)[end];

    // If there is only one token, it has to be a variable or constant
    if (start == end) {
        if (!(startToken.getType() == TokenType::ALPHANUM or startToken.getType() == TokenType::CONST)) {
            throw ParserException("Invalid factor: Const or Var missing");
        }
        return;
    }

    // If there is more than one token, it has to be "( expr )"
    if (start < end) {
        if (startToken.getType() == TokenType::LEFT_PARENTHESIS and
            endToken.getType() == TokenType::RIGHT_PARENTHESIS) {
            isAssignmentExpr(infixTokens, start + 1, end - 1);
            return;
        }
        else {
            throw ParserException("Invalid factor: Invalid const, var or bracketed expression");
        }
    }
    throw ParserException("Invalid factor: factor missing");
}
