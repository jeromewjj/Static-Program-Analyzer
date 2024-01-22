#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "CfgNodeType.h"
#include "unordered_set"

class CfgNode {
public:
    explicit CfgNode(CfgNodeType type, int nodeId, std::string procName)
        : type(type), nodeId(nodeId), procName(std::move(procName)){};

    virtual void addStmtNum(int stmt_number);
    virtual void addChild(std::shared_ptr<CfgNode>& child);

    [[nodiscard]] std::vector<std::shared_ptr<CfgNode>> getChildren() const {
        return children;
    }
    [[nodiscard]] std::unordered_set<int> getChildrenIds() const {
        return childrenIds;
    };
    [[nodiscard]] std::unordered_set<int> getStmts() const {
        return nodeStmts;
    };
    [[nodiscard]] CfgNodeType getType() const {
        return type;
    };
    [[nodiscard]] int getNodeId() const {
        return nodeId;
    }
    [[nodiscard]] std::string getProcName() const {
        return procName;
    }
    [[nodiscard]] std::string toString() const;

protected:
    int nodeId;
    std::unordered_set<int> nodeStmts;
    std::unordered_set<int> childrenIds;
    CfgNodeType type;
    std::vector<std::shared_ptr<CfgNode>> children;
    std::string procName;
};
