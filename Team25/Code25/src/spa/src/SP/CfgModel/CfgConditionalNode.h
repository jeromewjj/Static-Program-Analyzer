#pragma once
#include <utility>

#include "CfgNode.h"

class CfgConditionalNode : public CfgNode {
public:
    explicit CfgConditionalNode(int nodeId, std::string procName)
        : CfgNode(CfgNodeType::CONDITIONAL, nodeId, std::move(procName)){};
    void addStmtNum(int stmt_number) override;
    void addChild(std::shared_ptr<CfgNode>& child) override;
};
