#pragma once
#include "ASTNode.h"
#include "StmtListNode.h"
#include "general/helper.h"

class ProcedureNode : public ASTNode {
public:
    explicit ProcedureNode(const std::string& procName) : ASTNode(NodeType::PROCEDURE, procName) {
        addChild(std::make_shared<StmtListNode>());
    };

    void setStmtList(std::shared_ptr<StmtListNode> stmtListNode) {
        children[0] = stmtListNode;
    }

    std::string getName() const {
        return ASTNode::getValue();
    }

    std::shared_ptr<StmtListNode> getStmtList() const {
        //        helper::ASSERT(children.size() == 1, "Procedure has invalid num of StmtList: " +
        //        std::to_string(children.size()));
        return std::static_pointer_cast<StmtListNode>(children[0]);
    }

    void acceptVisitor(ExtractEntityVisitor& visitor) const override {
        auto sharedThis = std::static_pointer_cast<const ProcedureNode>(shared_from_this());
        visitor.extractEntity(sharedThis);
    };
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override{};
};
