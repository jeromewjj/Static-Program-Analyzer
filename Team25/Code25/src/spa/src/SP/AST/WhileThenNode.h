#pragma once
#include <cassert>

#include "Expression.h"
#include "StatementNode.h"
#include "StmtListNode.h"

class WhileThenNode : public StatementNode {
public:
    explicit WhileThenNode(int stmtNum) : StatementNode(NodeType::WHILE_THEN, "", stmtNum) {}
    WhileThenNode(const ASTNodePtr& conditionNode, const std::shared_ptr<StmtListNode>& thenNode, int stmtNum)
        : StatementNode(NodeType::WHILE_THEN, "", stmtNum) {
        addChild(conditionNode);
        addChild(thenNode);
    }

    void acceptVisitor(ExtractEntityVisitor& visitor) const override {
        std::shared_ptr<const WhileThenNode> sharedThis =
            std::static_pointer_cast<const WhileThenNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    }
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override {
        StatementNode::acceptVisitor(visitor);
    }

    std::shared_ptr<Expression> getConditionNode() const {
        assert(children.size() == 2);
        return std::static_pointer_cast<Expression>(children[0]);
    }

    std::shared_ptr<StmtListNode> getThenNode() const {
        assert(children.size() == 2);
        return std::static_pointer_cast<StmtListNode>(children[1]);
    }
};