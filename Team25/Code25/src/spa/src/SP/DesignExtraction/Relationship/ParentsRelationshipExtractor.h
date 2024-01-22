#pragma once
#include "RelationshipExtractor.h"

class ParentsRelationshipExtractor : public RelationshipExtractor {
public:
    explicit ParentsRelationshipExtractor(const std::shared_ptr<PKBAdapter>& pkbAdapter)
        : pkbAdapter(pkbAdapter), parentChildSet(std::make_shared<std::unordered_set<std::pair<int, int>>>()) {}

    void extractRelationshipAndFlush(const ASTNodePtr& rootNode) override {
        extractRelationship(rootNode);
        flush();
    };

    void extractRelationship(const ASTNodePtr& rootNode) override;
    void flush() override;

    [[nodiscard]] auto getParentChildSet() const {
        return parentChildSet;
    }

private:
    // set< parStmt, childStmt >
    const std::shared_ptr<std::unordered_set<std::pair<int, int>>> parentChildSet;
    const std::shared_ptr<PKBAdapter> pkbAdapter;
};