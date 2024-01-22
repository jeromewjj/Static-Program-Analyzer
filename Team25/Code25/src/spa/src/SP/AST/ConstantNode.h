#pragma once
#include "Expression.h"

class ConstantNode : public Expression {
public:
    explicit ConstantNode(const std::string& intValue) : Expression(NodeType::CONSTANT, intValue) {
        try {
            value = std::stoi(intValue);
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("ConstantNode - Invalid argument: " + intValue);
        } catch (const std::out_of_range& e) {
            throw std::runtime_error("ConstantNode - Out of range: " + intValue);
        }
    }

    [[nodiscard]] int getIntValue() const {
        return value;
    }
    void acceptVisitor(ExtractEntityVisitor& visitor) const override {
        std::shared_ptr<const ConstantNode> sharedThis =
            std::static_pointer_cast<const ConstantNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    }
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override {}

private:
    int value;
};