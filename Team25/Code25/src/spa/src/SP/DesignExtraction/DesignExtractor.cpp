#include "DesignExtractor.h"

#include "SP/AST/ASTNode.h"
#include "SP/DesignExtraction/CFG/CfgExtractor.h"
#include "SP/DesignExtraction/Relationship/CallsRelationshipExtractor.h"
#include "SP/DesignExtraction/Relationship/FollowsRelationshipExtractor.h"
#include "SP/DesignExtraction/Relationship/ModifiesRelationshipExtractor.h"
#include "SP/DesignExtraction/Relationship/ParentsRelationshipExtractor.h"
#include "SP/DesignExtraction/Relationship/UsesRelationshipExtractor.h"

void DesignExtractor::extractDesignAndPopulatePKB(const ASTNodePtr& rootNode) {
    // extract entities
    EntityExtractorManager entityExtractorManager{rootNode, pkbAdapter};
    entityExtractorManager.extractAndFlush();

    // extract relationships
    RelationshipExtractorManager manager{};

    // Create and add relationship extractors
    addRelationshipExtractor<ParentsRelationshipExtractor>(manager);
    addRelationshipExtractor<FollowsRelationshipExtractor>(manager);
    addRelationshipExtractor<ModifiesRelationshipExtractor>(manager);
    addRelationshipExtractor<UsesRelationshipExtractor>(manager);
    addRelationshipExtractor<CallsRelationshipExtractor>(manager);

    manager.extractRelationshipsAndFlush(rootNode);

    CfgExtractor cfgExtractor{};
    std::shared_ptr<Cfg> cfgManager = cfgExtractor.extractProgram((const shared_ptr<ProgramNode>&)rootNode);
    cfgManager->populatePkb(pkbAdapter);
}

// ai-gen start (gpt3, 3)
template <typename RelationshipExtractorType>
void DesignExtractor::addRelationshipExtractor(RelationshipExtractorManager& manager) {
    RelationshipExtractorType extractor{pkbAdapter};
    auto relationshipExtractor = std::make_shared<RelationshipExtractorType>(extractor);
    manager.addRelationshipExtractor(relationshipExtractor);
}
// ai-gen end