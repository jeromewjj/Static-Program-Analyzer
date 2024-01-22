#pragma once
#include <cassert>

#include "ASTNode.h"
#include "StatementNode.h"
#include "general/helper.h"

class StmtListNode : public ASTNode {
public:
    StmtListNode() : ASTNode(NodeType::STMT_LIST){};
    explicit StmtListNode(const std::vector<std::shared_ptr<StatementNode>>& stmts) : ASTNode(NodeType::STMT_LIST) {
        for (const auto& s : stmts) {
            addChild(s);
            n++;
        }
    };

    void addChild(const ASTNodePtr& child) override {
        n++;
        children.push_back(child);
    }

    std::shared_ptr<StatementNode> get(int idx) {
        //        assertCorrectNumOfChildren();
        helper::ASSERT(idx >= 0 && idx < n, "index out of bounds!");
        return std::static_pointer_cast<StatementNode>(children[idx]);
    }

    std::vector<std::shared_ptr<StatementNode>> getSortedStmts() const {
        //        assertCorrectNumOfChildren
        std::vector<std::shared_ptr<StatementNode>> stmts;
        stmts.reserve(children.size());
        for (const auto& c : children) {
            stmts.push_back(std::static_pointer_cast<StatementNode>(c));
        }
        return stmts;
    }

    void acceptVisitor(ExtractEntityVisitor& visitor) const override{};
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override{};

private:
    int n = 0;

    //    void assertCorrectNumOfChildren() {
    //        auto size = static_cast<size_t>(n);
    //        auto actualSize = children.size();
    //        const std::string wrongChildrenSizeMsg =
    //                "children_size(" + std::to_string(actualSize)
    //                + ") =/= " + "n(" + std::to_string(size) +")";
    //        helper::ASSERT(actualSize == size, wrongChildrenSizeMsg );
    //    }
};