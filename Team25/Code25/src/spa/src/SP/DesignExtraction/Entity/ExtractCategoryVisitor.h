#pragma once
#include <iostream>
#include <memory>
#include <unordered_set>
#include <utility>

#include "ExtractEntityVisitor.h"
#include "SP/DesignExtraction/PKBAdapter.h"

class StatementNode;

class ExtractCategoryVisitor {
public:
    explicit ExtractCategoryVisitor(const std::shared_ptr<PKBAdapter>& pkbAdapter)
        : pkbAdaptor(pkbAdapter), stmts(std::make_shared<std::vector<std::pair<NodeType, int>>>()) {}

    virtual void extractEntity(const std::shared_ptr<const StatementNode>& node) const;

    std::vector<std::pair<NodeType, int>> getStmts() {
        return *stmts;
    }
    void flushData() {
        pkbAdaptor->setStatements(*stmts);
        stmts->clear();
    }

private:
    void addStmt(const NodeType type, const int stmtNum) const {
        stmts->emplace_back(type, stmtNum);
    }
    const std::shared_ptr<std::vector<std::pair<NodeType, int>>> stmts;
    const std::shared_ptr<PKBAdapter> pkbAdaptor;
};