#include "AssignmentExpressionParser.h"

#include "SP/AST/BinaryExpressionNode.h"
#include "SP/AST/ConstantNode.h"
#include "SP/AST/Operators.h"
#include "SP/AST/VariableNode.h"
#include "SP/Parser/ParserException.h"

std::shared_ptr<Expression> AssignmentExpressionParser::postFixToTree(const shared_ptr<vector<Token>>& postFixTokens) {
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
        else if (isValidTokenType(token)) {
            // Operator token, pop two operands from the stack and create an operator node
            if (operandStack.size() < 2) {
                throw ParserException("Expression Parser: Insufficient operands for operator.");
            }
            std::shared_ptr<Expression> rightOperand = operandStack.top();
            operandStack.pop();
            std::shared_ptr<Expression> leftOperand = operandStack.top();
            operandStack.pop();

            // Create an operator node and add the operands as children
            std::shared_ptr<Expression> operatorNode =
                make_shared<BinaryExpressionNode>(identifyOperatorType(token), leftOperand, rightOperand);

            // Push the operator node back onto the operand stack
            operandStack.push(operatorNode);
        }
    }

    // After processing all tokens, the operand stack should contain the root of the AST
    if (operandStack.size() != 1) {
        throw runtime_error("Invalid expression.");
    }
    return operandStack.top();
}

int AssignmentExpressionParser::precedence(TokenType type) {
    switch (type) {
    case PLUS:
    case MINUS:
        return 1;
    case MULTIPLY:
    case DIVIDE:
    case MOD:
        return 2;
    default:
        return 0;
    }
}

std::string& AssignmentExpressionParser::identifyOperatorType(Token& token) {
    switch (token.getType()) {
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

bool AssignmentExpressionParser::isValidTokenType(Token& token) {
    if (token.getType() == PLUS || token.getType() == MINUS || token.getType() == MULTIPLY ||
        token.getType() == DIVIDE || token.getType() == MOD) {
        return true;
    }
    return false;
}

void AssignmentExpressionParser::validateExpression(const shared_ptr<vector<Token>>& infixTokens) {
    isAssignmentExpr(infixTokens, 0, infixTokens->size() - 1);
}
