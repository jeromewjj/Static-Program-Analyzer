#pragma once
#include "StatementNode.h"
#include "VariableNode.h"

using std::pair;
using std::string;
using std::unordered_set;
class AssignNode : public StatementNode {
public:
    AssignNode(const std::string& varName, int stmtNum) : StatementNode(NodeType::ASSIGN, "", stmtNum) {
        addChild(std::make_shared<VariableNode>(varName));
    }

    AssignNode(const std::shared_ptr<VariableNode>& varNode, const std::shared_ptr<Expression>& assignedExprNode,
               int stmtNum)
        : StatementNode(NodeType::ASSIGN, "", stmtNum) {
        addChild(varNode);
        addChild(assignedExprNode);
    }

    std::shared_ptr<VariableNode> getVarNode() const {
        return std::static_pointer_cast<VariableNode>(children[0]);
    }

    std::shared_ptr<Expression> getAssignedExpressionNode() const {
        return std::static_pointer_cast<Expression>(children[1]);
    }

    /**
     * @return a parenthesized fullExpression & a pointer to a set of partialExpressions
     */
    pair<string, std::shared_ptr<unordered_set<string>>> getParenthesizedExpression() const;

    void acceptVisitor(ExtractEntityVisitor& visitor) const override {
        std::shared_ptr<const AssignNode> sharedThis = std::static_pointer_cast<const AssignNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    }
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override {
        StatementNode::acceptVisitor(visitor);
    }
};
