#pragma once
#include <utility>

#include "ASTNode.h"

class StatementNode : public ASTNode {
public:
    StatementNode(NodeType type, const std::string& value, int stmtNum) : stmtNum(stmtNum), ASTNode(type, value) {}

    std::string toString() const override {
        return std::to_string(stmtNum) + ": " + ASTNode::toString();
    }

    int getStmtNum() const {
        return stmtNum;
    }

    void acceptVisitor(ExtractCategoryVisitor& visitor) const override {
        std::shared_ptr<const StatementNode> sharedThis =
            std::static_pointer_cast<const StatementNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    }
    void acceptVisitor(ExtractEntityVisitor& visitor) const override {}

private:
    const int stmtNum;
};
