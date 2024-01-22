#pragma once
#include "ASTNode.h"
#include "ProcedureNode.h"
#include "general/helper.h"

class ProgramNode : public ASTNode {
public:
    ProgramNode(const std::string& programName) : ASTNode(NodeType::PROGRAM, programName){};
    explicit ProgramNode(const std::string& programName, const std::vector<std::shared_ptr<ProcedureNode>>& procedures)
        : ASTNode(NodeType::PROGRAM, programName) {
        for (const auto& p : procedures) {
            addChild(p);
            n++;
        }
    };

    void addProcedure(const ASTNodePtr& procNode) {
        addChild(procNode);
    }

    void addChild(const ASTNodePtr& child) override {
        n++;
        children.push_back(child);
    }

    std::shared_ptr<ProcedureNode> get(int idx) {
        helper::ASSERT(idx >= 0 && idx < n, "index out of bounds!");
        return std::static_pointer_cast<ProcedureNode>(children[idx]);
    }

    std::vector<std::shared_ptr<ProcedureNode>> getProcedures() const {
        std::vector<std::shared_ptr<ProcedureNode>> stmts;
        stmts.reserve(children.size());
        for (const auto& c : children) {
            stmts.push_back(std::static_pointer_cast<ProcedureNode>(c));
        }
        return stmts;
    }

    void acceptVisitor(ExtractEntityVisitor& visitor) const override{};
    void acceptVisitor(ExtractCategoryVisitor& visitor) const override{};

private:
    // num of children procedures
    int n = 0;
};
