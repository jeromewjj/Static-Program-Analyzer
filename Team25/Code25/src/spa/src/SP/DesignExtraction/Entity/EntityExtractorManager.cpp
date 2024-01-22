#include "EntityExtractorManager.h"

#include "SP/AST/ASTNode.h"

void EntityExtractorManager::extractAndFlush() {
    ExtractEntityVisitor ev{pkbAdapter};
    ExtractCategoryVisitor cv{pkbAdapter};

    std::vector<std::shared_ptr<const ASTNode>> nodes = rootNode->breadthFirstTraversal();
    for (const auto& node : nodes) {
        node->acceptVisitor(ev);
        node->acceptVisitor(cv);
    }

    ev.flushData();
    cv.flushData();
}
