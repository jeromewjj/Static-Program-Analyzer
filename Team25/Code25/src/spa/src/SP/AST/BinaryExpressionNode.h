#pragma once
#include <cassert>

#include "Expression.h"

class BinaryExpressionNode : public Expression {
public:
    BinaryExpressionNode(const std::string& mathOperator, const std::shared_ptr<Expression>& lhsExpr,
                         const std::shared_ptr<Expression>& rhsExpr)
        : Expression(NodeType::BINARY_EXPRESSION, mathOperator) {
        addChild(lhsExpr);
        addChild(rhsExpr);
    }

    std::shared_ptr<Expression> LHS() const {
        assert(children.size() == 2);
        return std::static_pointer_cast<Expression>(children[0]);
    }

    std::shared_ptr<Expression> RHS() const {
        assert(children.size() == 2);
        return std::static_pointer_cast<Expression>(children[1]);
    }

    std::string getOperator() const {
        return getValue();
    }
};
