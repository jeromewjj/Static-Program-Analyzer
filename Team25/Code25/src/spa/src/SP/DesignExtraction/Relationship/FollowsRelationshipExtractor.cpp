#include "FollowsRelationshipExtractor.h"

#include <vector>

#include "SP/AST/StmtListNode.h"

void FollowsRelationshipExtractor::extractRelationship(const ASTNodePtr& rootNode) {
    std::vector<ASTNodePtr_VIEWONLY> nodes = rootNode->breadthFirstTraversal();
    for (const auto& n : nodes) {
        if (n->getType() == NodeType::STMT_LIST) {
            auto stmtList = std::static_pointer_cast<const StmtListNode>(n);
            auto sortedStmts = stmtList->getSortedStmts();

            // ai-gen start (gpt3, 3)
            for (size_t i = 0; i < sortedStmts.size() - 1; ++i) {
                std::pair<int, int> p = std::make_pair(sortedStmts[i]->getStmtNum(), sortedStmts[i + 1]->getStmtNum());
                followeeFollowerSet->insert(p);
            }
            // ai-gen end
        }
    }
}

void FollowsRelationshipExtractor::flush() {
    pkbAdapter->setFollowsRelationship(followeeFollowerSet);
    followeeFollowerSet->clear();
}
