#include "Cfg.h"

#include <queue>
#include <unordered_set>

void Cfg::addProcCfg(const std::shared_ptr<CfgNode>& cfgRootNode) {
    cfgRootNodes.push_back(cfgRootNode);
}

std::vector<std::shared_ptr<CfgNode>> Cfg::getRootNodes() {
    return cfgRootNodes;
}

std::vector<std::shared_ptr<const CfgNode>> Cfg::bfsSingleProc(const std::shared_ptr<CfgNode>& rootCfgNode) {
    std::vector<std::shared_ptr<const CfgNode>> visitedNodes;
    std::queue<std::shared_ptr<CfgNode>> nodeQueue;
    std::unordered_set<int> visited;

    nodeQueue.push(rootCfgNode);

    while (!nodeQueue.empty()) {
        std::shared_ptr<CfgNode> currentNode = nodeQueue.front();
        nodeQueue.pop();

        // Check if the node has already been visited from a different parent
        if (visited.find(currentNode->getNodeId()) == visited.end()) {
            // Add the current node to the list of visited nodes
            visitedNodes.push_back(currentNode);

            // Mark the current node as visited
            visited.insert(currentNode->getNodeId());

            // Create Node Block and add to PKB

            // Get the children of the current node and add them to the queue
            for (const std::shared_ptr<CfgNode>& child : currentNode->getChildren()) {
                nodeQueue.push(child);
            }
        }
    }

    return visitedNodes;
}

std::vector<std::vector<std::shared_ptr<const CfgNode>>> Cfg::bfsAllProcs() {
    std::vector<std::shared_ptr<CfgNode>> rootNodes = getRootNodes();
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> allBfsResults; // Vector to store all BFS results

    for (const std::shared_ptr<CfgNode>& rootNode : rootNodes) {
        std::vector<std::shared_ptr<const CfgNode>> bfsResult = bfsSingleProc(rootNode);
        allBfsResults.push_back(bfsResult); // Store the BFS result for this root node
    }

    return allBfsResults; // Return the vector of BFS results for all root nodes
}

void Cfg::populatePkb(const std::shared_ptr<PKBAdapter>& pkbAdapter) {
    std::unordered_set<CFGBlock> cfgBlockSet;
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> procs = bfsAllProcs();

    for (const std::vector<std::shared_ptr<const CfgNode>>& cfg : procs) {
        bool isStart = true;
        for (const std::shared_ptr<const CfgNode>& cfgNode : cfg) {
            CFGBlockType blockType;
            if (isStart) {
                blockType = CFGBlockType::START_PROC;
            }
            else if (cfgNode->getType() == CfgNodeType::END) {
                blockType = CFGBlockType::DUMMY;
            }
            else {
                blockType = CFGBlockType::NORMAL;
            }

            CFGBlock block{cfgNode->getNodeId(), cfgNode->getProcName(), blockType, cfgNode->getStmts(),
                           cfgNode->getChildrenIds()};

            cfgBlockSet.emplace(block);
            isStart = false;
        }
    }
    pkbAdapter->setCfgBlock(cfgBlockSet);
}
