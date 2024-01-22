#pragma once
#include <utility>

#include "CfgNode.h"

class CfgNormalNode : public CfgNode {
public:
    explicit CfgNormalNode(int nodeId, std::string procName)
        : CfgNode(CfgNodeType::NORMAL, nodeId, std::move(procName)){};
};
