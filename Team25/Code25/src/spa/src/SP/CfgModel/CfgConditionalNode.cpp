#include "CfgConditionalNode.h"

#include <stdexcept>

void CfgConditionalNode::addStmtNum(int stmt_number) {
    if (nodeStmts.size() == 1) {
        throw std::runtime_error("Adding multiple stmt numbers to conditional node");
    }
    CfgNode::addStmtNum(stmt_number);
}

void CfgConditionalNode::addChild(std::shared_ptr<CfgNode>& child) {
    if (children.size() == 2) {
        throw std::runtime_error("Adding third child to CFG Conditional node");
    }
    childrenIds.emplace(child->getNodeId());
    children.push_back(child);
}
