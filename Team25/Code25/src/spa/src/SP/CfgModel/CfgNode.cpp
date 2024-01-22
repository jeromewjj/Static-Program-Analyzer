#include "CfgNode.h"

#include <stdexcept>

void CfgNode::addStmtNum(int stmt_number) {
    nodeStmts.emplace(stmt_number);
}

void CfgNode::addChild(std::shared_ptr<CfgNode>& child) {
    if (children.size() == 1) {
        throw std::runtime_error("Adding second child to non-conditional node");
    }
    childrenIds.emplace(child->getNodeId());
    children.push_back(child);
}

std::string CfgNode::toString() const {
    std::string result = "Node ID: " + std::to_string(nodeId) + ", ProcName: " + procName +
                         ", Type: " + cfgNodeTypeToString(type) + ", Stmt Numbers: (";

    // Append statement numbers
    for (int stmt : nodeStmts) {
        result += std::to_string(stmt) + ",";
    }
    result += ")";
    // Append children information
    result += " Children: (";
    for (const auto& childId : childrenIds) {
        result += std::to_string(childId) + ",";
    }
    result += ")";
    return result;
}