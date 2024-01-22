#pragma once

#include "SP/AST/ASTNode.h"

// abstract class
class RelationshipExtractor {
public:
    virtual void extractRelationshipAndFlush(const ASTNodePtr& rootNode) = 0;
    virtual void extractRelationship(const ASTNodePtr& rootNode) = 0;
    virtual void flush() = 0;

private:
    const std::shared_ptr<PKBAdapter> pkbAdapter;
};
