#pragma once
#include "RelationshipExtractor.h"

class FollowsRelationshipExtractor : public RelationshipExtractor {
public:
    explicit FollowsRelationshipExtractor(std::shared_ptr<PKBAdapter> pkbAdapter)
        : pkbAdapter(pkbAdapter), followeeFollowerSet(std::make_shared<std::unordered_set<std::pair<int, int>>>()) {}

    void extractRelationshipAndFlush(const ASTNodePtr& rootNode) override {
        extractRelationship(rootNode);
        flush();
    };

    void extractRelationship(const ASTNodePtr& rootNode) override;
    void flush() override;

    [[nodiscard]] auto getfolloweeFollowerSet() const {
        return followeeFollowerSet;
    }

private:
    /**
     * @note: followee always has a smaller statement number compared to follower
     * @example: pair<followee, follower>
     */
    const std::shared_ptr<std::unordered_set<std::pair<int, int>>> followeeFollowerSet;
    const std::shared_ptr<PKBAdapter> pkbAdapter;
};
