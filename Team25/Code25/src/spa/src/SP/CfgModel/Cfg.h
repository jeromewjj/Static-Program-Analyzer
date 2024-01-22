#pragma once
#include <vector>

#include "CfgNode.h"
#include "SP/DesignExtraction/PKBAdapter.h"

class Cfg {
public:
    Cfg() = default;
    void addProcCfg(const std::shared_ptr<CfgNode>& cfgRootNode);
    std::vector<std::shared_ptr<CfgNode>> getRootNodes();
    [[nodiscard]] std::vector<std::shared_ptr<const CfgNode>> bfsSingleProc(const std::shared_ptr<CfgNode>& rootNode);
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> bfsAllProcs();
    void populatePkb(const std::shared_ptr<PKBAdapter>& pkbAdapter);

private:
    std::vector<std::shared_ptr<CfgNode>> cfgRootNodes;
};
