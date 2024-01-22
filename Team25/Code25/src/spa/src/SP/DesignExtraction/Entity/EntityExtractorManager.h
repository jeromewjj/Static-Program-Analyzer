#pragma once

#include "SP/AST/ASTNode.h"

class EntityExtractorManager {
public:
    EntityExtractorManager(const ASTNodePtr& rootNode, const std::shared_ptr<PKBAdapter>& pkbAdapter)
        : pkbAdapter(pkbAdapter), rootNode(rootNode) {}

    void extractAndFlush();

    const ASTNodePtr& rootNode;
    std::shared_ptr<PKBAdapter> pkbAdapter;
};
