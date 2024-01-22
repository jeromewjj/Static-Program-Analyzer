#include "AssignNode.h"

#include "BinaryExpressionNode.h"
#include "ConstantNode.h"
#include "UnaryExpressionNode.h"

std::string getExpression(const std::shared_ptr<Expression>& node,
                          std::shared_ptr<std::unordered_set<std::string>> storage) {
    if (node->getType() == NodeType::VARIABLE) {
        auto var = std::static_pointer_cast<const VariableNode>(node);
        std::string expr = "(" + var->getName() + ")";
        storage->insert(expr);
        return expr;
    }
    else if (node->getType() == NodeType::CONSTANT) {
        auto constant = std::static_pointer_cast<const ConstantNode>(node);
        std::string expr = "(" + constant->getValue() + ")";
        storage->insert(expr);
        return expr;
    }

    // unary and binary expressions
    if (node->getType() == NodeType::UNARY_EXPRESSION) {
        auto unaryExpr = std::static_pointer_cast<const UnaryExpressionNode>(node);
        std::string childExpr = getExpression(unaryExpr->getChildExpression(), storage);
        std::string expr = "(" + unaryExpr->getOperator() + childExpr + ")";
        storage->insert(expr);
        return expr;
    }
    else if (node->getType() == NodeType::BINARY_EXPRESSION) {
        auto binaryExpr = std::static_pointer_cast<const BinaryExpressionNode>(node);
        std::string lhsExpr = getExpression(binaryExpr->LHS(), storage);
        std::string rhsExpr = getExpression(binaryExpr->RHS(), storage);
        std::string expr = "(" + lhsExpr + binaryExpr->getOperator() + rhsExpr + ")";
        storage->insert(expr);
        return expr;
    }

    throw std::runtime_error("Expression node is not constant, variable or UNARY "
                             "and BINARY Expressions");
}

pair<string, std::shared_ptr<unordered_set<string>>> AssignNode::getParenthesizedExpression() const {
    auto subExpressions = std::make_shared<std::unordered_set<string>>();
    std::string fullExpression = getExpression(getAssignedExpressionNode(), subExpressions);

    return {fullExpression, subExpressions};
}
