#pragma once
#include <cassert>

#include "Expression.h"

class UnaryExpressionNode : public Expression {
public:
    UnaryExpressionNode(const std::string& mathOperator, const std::shared_ptr<Expression>& expr)
        : Expression(NodeType::UNARY_EXPRESSION, mathOperator) {
        addChild(expr);
    }

    std::shared_ptr<Expression> getChildExpression() const {
        //        assert(children.size() == 1);
        return std::static_pointer_cast<Expression>(children[0]);
    }

    std::string getOperator() const {
        return getValue();
    }
};
