#include "ASTNode.h"

#include <vector>

// ai-gen start (gpt3, 1)
std::vector<std::shared_ptr<const ASTNode>> ASTNode::breadthFirstTraversal() const {
    std::vector<std::shared_ptr<const ASTNode>> resNodes;
    std::queue<std::shared_ptr<const ASTNode>> nodeQueue;
    nodeQueue.push(shared_from_this());

    while (!nodeQueue.empty()) {
        auto cur = nodeQueue.front();
        nodeQueue.pop();

        resNodes.push_back(cur);

        // enqueue children for processing
        auto curNodeChildren = cur->getChildren();
        for (const auto& child : curNodeChildren) {
            nodeQueue.push(child);
        }
    }
    return resNodes;
}

// std::vector<std::shared_ptr<const ASTNode>> ASTNode::postorderTraversal() const {
//     std::vector<std::shared_ptr<const ASTNode>> resNodes;
//
//     // Helper function for postorder traversal
//     std::function<void(const std::shared_ptr<const ASTNode>&)> postorderHelper;
//     postorderHelper = [&postorderHelper, &resNodes](const std::shared_ptr<const ASTNode>& node) {
//       if (!node) { return; }
//
//       // Visit left subtree
//       if (node->getChildren().size() > 0) {
//         postorderHelper(node->getChildren()[0]);
//       }
//
//       // Visit right subtrees
//       for (size_t i = 1; i < node->getChildren().size(); ++i) {
//         postorderHelper(node->getChildren()[i]);
//       }
//
//       // Visit current node
//       resNodes.push_back(node);
//     };
//
//     // Start postorder traversal from the root
//     postorderHelper(shared_from_this());
//
//     return resNodes;
// }
//  ai-gen stop