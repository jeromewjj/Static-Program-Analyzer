#pragma once

#include "ASTNode.h"
#include "Expression.h"
#include "SP/DesignExtraction/Entity/ExtractEntityVisitor.h"

class VariableNode : public Expression {
public:
    explicit VariableNode(const std::string& varName) : Expression(NodeType::VARIABLE, varName) {}
    void acceptVisitor(ExtractEntityVisitor& visitor) const override {
        std::shared_ptr<const VariableNode> sharedThis =
            std::static_pointer_cast<const VariableNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    }
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override {}

    std::string getName() const {
        return ASTNode::getValue();
    }
};
