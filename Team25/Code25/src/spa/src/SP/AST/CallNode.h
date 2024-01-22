#pragma once
#include "StatementNode.h"

class CallNode : public StatementNode {
public:
    CallNode(const std::string& procName, int stmtNum) : StatementNode(NodeType::CALL, procName, stmtNum) {}

    std::string getProcedureName() const {
        return ASTNode::getValue();
    }

    void acceptVisitor(ExtractEntityVisitor& visitor) const override {
        std::shared_ptr<const CallNode> sharedThis = std::static_pointer_cast<const CallNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    }

    void acceptVisitor(ExtractCategoryVisitor& visitor) const override {
        StatementNode::acceptVisitor(visitor);
    }
};