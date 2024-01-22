#pragma once

#include "SP/AST/ASTNode.h"
#include "SP/DesignExtraction/Entity/EntityExtractorManager.h"
#include "SP/DesignExtraction/Relationship/RelationshipExtractorManager.h"

class DesignExtractor {
public:
    explicit DesignExtractor(std::shared_ptr<PKBAdapter> pkbAdapter) : pkbAdapter(pkbAdapter){};
    void extractDesignAndPopulatePKB(const ASTNodePtr& rootNode);

private:
    std::shared_ptr<PKBAdapter> pkbAdapter;

    template <typename RelationshipExtractorType> void addRelationshipExtractor(RelationshipExtractorManager& manager);
};
