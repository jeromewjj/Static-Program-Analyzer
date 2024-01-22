#pragma once
#include "ASTNode.h"

class Expression : public ASTNode {
public:
    Expression(NodeType type, const std::string& value) : ASTNode(type, value) {}
    void acceptVisitor(ExtractEntityVisitor& visitor) const override{};
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override{};
};