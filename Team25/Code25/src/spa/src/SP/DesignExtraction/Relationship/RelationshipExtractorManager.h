#pragma once

#include <memory>

#include "RelationshipExtractor.h"
#include "SP/AST/ASTNode.h"

class RelationshipExtractorManager {
public:
    void extractRelationshipsAndFlush(const ASTNodePtr& rootNode) {
        for (const auto& x : relationshipExtractors) {
            x->extractRelationshipAndFlush(rootNode);
        }
    }

    void extractRelationships(const ASTNodePtr& rootNode) {
        for (const auto& x : relationshipExtractors) {
            x->extractRelationship(rootNode);
        }
    }

    void addRelationshipExtractor(const std::shared_ptr<RelationshipExtractor>& x) {
        relationshipExtractors.insert(x);
    }

private:
    std::unordered_set<std::shared_ptr<RelationshipExtractor>> relationshipExtractors;
};
