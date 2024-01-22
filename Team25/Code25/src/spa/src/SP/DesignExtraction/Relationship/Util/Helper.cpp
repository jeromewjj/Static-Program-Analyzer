#include "Helper.h"

#include "SP/AST/CallNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/WhileThenNode.h"

using std::pair;
using std::queue;
using std::string;
using std::unordered_map;
using std::unordered_set;

// ai-gen start (gpt3, 1)
unordered_map<string, unordered_set<string>>
Helper::getTransitiveClosure(unordered_map<string, unordered_set<string>> s) {

    unordered_map<std::string, std::unordered_set<std::string>> closure = s;

    // Initialize a queue for BFS
    queue<std::string> toVisit{};

    // Mark nodes as visited to avoid infinite loops
    unordered_map<std::string, bool> visited;

    for (const auto& entry : s) {
        const std::string& node = entry.first;
        const std::unordered_set<std::string>& reachableNodes = entry.second;

        // Mark the current node as visited
        visited[node] = true;

        // Add the initially reachable nodes to the queue
        for (const std::string& reachableNode : reachableNodes) {
            toVisit.push(reachableNode);
        }

        while (!toVisit.empty()) {
            const std::string& currentNode = toVisit.front();
            toVisit.pop();

            // Check if the current node exists in the input map
            if (s.find(currentNode) == s.end()) {
                continue;
            }

            // Find nodes reachable from the current node
            const std::unordered_set<std::string>& nextReachableNodes = s.at(currentNode);

            for (const std::string& nextNode : nextReachableNodes) {
                // If the node is not already in the closure, add it
                if (closure[node].find(nextNode) == closure[node].end()) {
                    closure[node].insert(nextNode);

                    // Add the newly reachable node to the queue for further
                    // exploration
                    toVisit.push(nextNode);
                }
            }
        }
    }

    return closure;
}
// ai-gen end

std::unordered_set<std::string> Helper::getVarNamesInSubtree(const ASTNodePtr_VIEWONLY& node) {
    std::unordered_set<string> varNames{};
    auto nodes = node->breadthFirstTraversal();
    for (const auto& n : nodes) {
        if (n->getType() == NodeType::VARIABLE) {
            std::shared_ptr<const VariableNode> varNode = std::static_pointer_cast<const VariableNode>(n);
            varNames.insert(varNode->getName());
        }
    }
    return varNames;
}
