#include "ParentsRelationshipExtractor.h"

#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/WhileThenNode.h"

void ParentsRelationshipExtractor::extractRelationship(const ASTNodePtr& rootNode) {
    std::vector<ASTNodePtr_VIEWONLY> nodes = rootNode->breadthFirstTraversal();
    for (const auto& n : nodes) {
        if (n->getType() == NodeType::WHILE_THEN) {
            auto whileNode = std::static_pointer_cast<const WhileThenNode>(n);
            for (const auto& child : whileNode->getThenNode()->getSortedStmts()) {
                std::pair<int, int> parChildPair{whileNode->getStmtNum(), child->getStmtNum()};
                parentChildSet->insert(parChildPair);
            }
        }
        else if (n->getType() == NodeType::IF_THEN_ELSE) {
            auto ifNode = std::static_pointer_cast<const IfThenElseNode>(n);
            for (const auto& child : ifNode->getThenNode()->getSortedStmts()) {
                std::pair<int, int> parChildPair{ifNode->getStmtNum(), child->getStmtNum()};
                parentChildSet->insert(parChildPair);
            }
            for (const auto& child : ifNode->getElseNode()->getSortedStmts()) {
                std::pair<int, int> parChildPair{ifNode->getStmtNum(), child->getStmtNum()};
                parentChildSet->insert(parChildPair);
            }
        }
    }
}

void ParentsRelationshipExtractor::flush() {
    pkbAdapter->setParentsRelationship(parentChildSet);
    parentChildSet->clear();
}
