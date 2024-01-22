#pragma once
#include <cassert>

#include "Expression.h"
#include "StatementNode.h"
#include "StmtListNode.h"

class IfThenElseNode : public StatementNode {
public:
    explicit IfThenElseNode(int stmtNum) : StatementNode(NodeType::IF_THEN_ELSE, "", stmtNum) {}
    IfThenElseNode(const ASTNodePtr& conditionNode, const std::shared_ptr<StmtListNode>& thenStmtList,
                   const std::shared_ptr<StmtListNode>& elseStmtList, int stmtNum)
        : StatementNode(NodeType::IF_THEN_ELSE, "", stmtNum) {
        addChild(conditionNode);
        addChild(thenStmtList);
        addChild(elseStmtList);
    }

    void acceptVisitor(ExtractEntityVisitor& visitor) const override {
        std::shared_ptr<const IfThenElseNode> sharedThis =
            std::static_pointer_cast<const IfThenElseNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    }
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override {
        StatementNode::acceptVisitor(visitor);
    }

    std::shared_ptr<Expression> getConditionNode() const {
        assert(children.size() == 3);
        return std::static_pointer_cast<Expression>(children[0]);
    }

    std::shared_ptr<StmtListNode> getThenNode() const {
        assert(children.size() == 3);
        return std::static_pointer_cast<StmtListNode>(children[1]);
    }

    std::shared_ptr<StmtListNode> getElseNode() const {
        assert(children.size() == 3);
        return std::static_pointer_cast<StmtListNode>(children[2]);
    }
};