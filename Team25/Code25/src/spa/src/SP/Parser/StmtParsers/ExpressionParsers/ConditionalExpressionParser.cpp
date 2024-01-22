#include "ConditionalExpressionParser.h"

#include "SP/AST/BinaryExpressionNode.h"
#include "SP/AST/ConstantNode.h"
#include "SP/AST/Operators.h"
#include "SP/AST/UnaryExpressionNode.h"
#include "SP/AST/VariableNode.h"
#include "SP/Parser/ParserException.h"

std::shared_ptr<Expression> ConditionalExpressionParser::postFixToTree(const shared_ptr<vector<Token>>& postFixTokens) {
    stack<std::shared_ptr<Expression>> operandStack;

    for (Token& token : *postFixTokens) {
        if (token.getType() == ALPHANUM) {
            // Operand token, create an AST node for it and push it onto the operand stack
            std::shared_ptr<VariableNode> operandNode = make_shared<VariableNode>(token.getValue());
            operandStack.push(operandNode);
        }
        else if (token.getType() == CONST) {
            std::shared_ptr<ConstantNode> operandNode = make_shared<ConstantNode>(token.getValue());
            operandStack.push(operandNode);
        }
        else if (token.getType() == NOT) {
            // Create an operator node and add the operands as children
            if (operandStack.empty()) {
                throw ParserException("Cond Expression Parser: Insufficient operands for unary operator.");
            }
            std::shared_ptr<Expression> childOperand = operandStack.top();
            operandStack.pop();
            std::shared_ptr<UnaryExpressionNode> operatorNode =
                make_shared<UnaryExpressionNode>(identifyOperatorType(token), childOperand);

            // Push the operator node back onto the operand stack
            operandStack.push(operatorNode);
        }
        else if (isValidTokenType(token)) {
            // Operator token, pop two operands from the stack and create an operator node
            if (operandStack.size() < 2) {
                throw ParserException("Cond Expression Parser: Insufficient operands for binary operator.");
            }
            std::shared_ptr<Expression> rightOperand = operandStack.top();
            operandStack.pop();
            std::shared_ptr<Expression> leftOperand = operandStack.top();
            operandStack.pop();

            std::shared_ptr<BinaryExpressionNode> operatorNode =
                make_shared<BinaryExpressionNode>(identifyOperatorType(token), leftOperand, rightOperand);

            // Push the operator node back onto the operand stack
            operandStack.push(operatorNode);
        }
        else {
            throw ParserException("Cond Expression Parser: invalid token detected");
        }
    }

    // After processing all tokens, the operand stack should contain the root of the AST
    if (operandStack.size() != 1) {
        throw ParserException("Cond Expression Parser: Invalid expression");
    }
    return operandStack.top();
}

int ConditionalExpressionParser::precedence(TokenType type) {
    switch (type) {
    case MORE_THAN:
    case MORE_THAN_EQUAL:
    case LESS_THAN:
    case LESS_THAN_EQUAL:
    case DOUBLE_EQUAL:
    case NOT_EQUAL:
    case AND:
    case OR:
        return 1;
    case MULTIPLY:
    case DIVIDE:
    case MOD:
        return 3;
    case NOT:
    case PLUS:
    case MINUS:
        return 2;
    default:
        return 0;
    }
}

string& ConditionalExpressionParser::identifyOperatorType(Token& token) {
    switch (token.getType()) {
    case TokenType::MORE_THAN:
        return const_cast<string&>(RelOperator::GREATER_THAN);
    case TokenType::MORE_THAN_EQUAL:
        return const_cast<string&>(RelOperator::GREATER_THAN_OR_EQUALS);
    case TokenType::LESS_THAN:
        return const_cast<string&>(RelOperator::LESS_THAN);
    case TokenType::LESS_THAN_EQUAL:
        return const_cast<string&>(RelOperator::LESS_THAN_OR_EQUALS);
    case TokenType::DOUBLE_EQUAL:
        return const_cast<string&>(RelOperator::EQUALS);
    case TokenType::NOT_EQUAL:
        return const_cast<string&>(RelOperator::NOT_EQUALS);
    case TokenType::NOT:
        return const_cast<string&>(UnaryExprOperator::NOT);
    case TokenType::AND:
        return const_cast<string&>(RelOperator::AND);
    case TokenType::OR:
        return const_cast<string&>(RelOperator::OR);

    case TokenType::PLUS:
        return const_cast<string&>(BinaryExprOperator::ADD);
    case TokenType::MINUS:
        return const_cast<string&>(BinaryExprOperator::SUBTRACT);
    case TokenType::MULTIPLY:
        return const_cast<string&>(BinaryExprOperator::MULTIPLY);
    case TokenType::DIVIDE:
        return const_cast<string&>(BinaryExprOperator::DIVIDE);
    case TokenType::MOD:
        return const_cast<string&>(BinaryExprOperator::MOD);
        // Add cases for other operators as needed
    default:
        throw runtime_error("Invalid operator token.");
    }
}

bool ConditionalExpressionParser::isValidTokenType(Token& token) {
    if (token.getType() == MORE_THAN || token.getType() == LESS_THAN || token.getType() == MORE_THAN_EQUAL ||
        token.getType() == LESS_THAN_EQUAL || token.getType() == NOT_EQUAL || token.getType() == NOT ||
        token.getType() == AND || token.getType() == OR || token.getType() == DOUBLE_EQUAL || token.getType() == PLUS ||
        token.getType() == MINUS || token.getType() == MULTIPLY || token.getType() == DIVIDE ||
        token.getType() == MOD) {
        return true;
    }
    return false;
}

void ConditionalExpressionParser::validateExpression(const shared_ptr<vector<Token>>& infixTokens) {
    isConditionalExpr(infixTokens, 0, infixTokens->size() - 1);
}

void ConditionalExpressionParser::isConditionalExpr(const shared_ptr<vector<Token>>& infixTokens, size_t start,
                                                    size_t end) {
    const Token& startToken = (*infixTokens)[start];
    const Token& secondToken = (*infixTokens)[start + 1];
    const Token& endToken = (*infixTokens)[end];

    if (startToken.getType() == TokenType::NOT && secondToken.getType() == LEFT_PARENTHESIS &&
        endToken.getType() == RIGHT_PARENTHESIS) {
        isConditionalExpr(infixTokens, start + 2, end - 1);
        return;
    }

    int parenthesis_count = 0;

    for (size_t i = start; i <= end; ++i) {
        const Token& token = infixTokens->at(i);

        if (parenthesis_count == 0 && (token.getType() == AND || token.getType() == OR)) {
            Token& prevToken = infixTokens->at(i - 1);
            Token& nextToken = infixTokens->at(i + 1);
            if (startToken.getType() == LEFT_PARENTHESIS && prevToken.getType() == RIGHT_PARENTHESIS &&
                nextToken.getType() == LEFT_PARENTHESIS && endToken.getType() == RIGHT_PARENTHESIS) {
                isConditionalExpr(infixTokens, start + 1, i - 2);
                isConditionalExpr(infixTokens, i + 2, end - 1);
                return;
            }
            throw ParserException("Invalid conditional expression: Missing brackets");
        }
        else if (token.getType() == TokenType::LEFT_PARENTHESIS) {
            parenthesis_count++;
        }
        else if (token.getType() == TokenType::RIGHT_PARENTHESIS) {
            parenthesis_count--;
        }
    }
    isRelExpression(infixTokens, start, end);
}

void ConditionalExpressionParser::isRelExpression(const shared_ptr<vector<Token>>& infixTokens, size_t start,
                                                  size_t end) {
    for (size_t i = start; i <= end; ++i) {
        const Token& token = infixTokens->at(i);

        if (token.getType() == MORE_THAN || token.getType() == LESS_THAN || token.getType() == MORE_THAN_EQUAL ||
            token.getType() == LESS_THAN_EQUAL || token.getType() == DOUBLE_EQUAL || token.getType() == NOT_EQUAL) {
            isRelFactor(infixTokens, start, i - 1);
            isRelFactor(infixTokens, i + 1, end);
            return;
        }
    }
    throw ParserException("Invalid rel expression: Missing rel operator");
}

void ConditionalExpressionParser::isRelFactor(const shared_ptr<vector<Token>>& infixTokens, size_t start, size_t end) {
    const Token& startToken = (*infixTokens)[start];
    const Token& endToken = (*infixTokens)[end];

    // If there is only one token, it has to be a variable or constant
    if (start == end) {
        if (!(startToken.getType() == TokenType::ALPHANUM or startToken.getType() == TokenType::CONST)) {
            throw ParserException("Invalid factor: Const or Var missing");
        }
        return;
    }

    if (start < end) {
        isAssignmentExpr(infixTokens, start, end);
        return;
    }
    throw ParserException("Invalid rel_factor: rel_factor missing");
}
