#pragma once
#include <utility>

#include "CfgNode.h"

class CfgEndNode : public CfgNode {
public:
    explicit CfgEndNode(int nodeId, std::string procName) : CfgNode(CfgNodeType::END, nodeId, std::move(procName)){};
};
