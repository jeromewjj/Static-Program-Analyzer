#include "../../AST/MockASTs.h"
#include "SP/DesignExtraction/Relationship/FollowsRelationshipExtractor.h"
#include "catch.hpp"

TEST_CASE("Should extract Follows from If & While statement nodes [1,2,3]", "[FollowsRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    FollowsRelationshipExtractor f_x{pkbAdapter};

    auto rootNode = MockASTs::mock1();
    f_x.extractRelationship(rootNode);
    auto followsSet = f_x.getfolloweeFollowerSet();

    // expected
    // ordering of [1,2,3]
    std::unordered_set<std::pair<int, int>> EXPECTED_FOLLOWS_SET{{1, 2}, {2, 3}};

    REQUIRE(*followsSet == EXPECTED_FOLLOWS_SET);
}

TEST_CASE("Should extract Follows from If & While statement nodes", "[FollowsRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    FollowsRelationshipExtractor f_x{pkbAdapter};

    auto rootNode = MockASTs::mock2();
    f_x.extractRelationship(rootNode);
    auto followsSet = f_x.getfolloweeFollowerSet();

    // expected
    // ordering of [1,2,4,5]
    std::unordered_set<std::pair<int, int>> EXPECTED_FOLLOWS_SET{{1, 2}, {2, 4}, {4, 5}};

    REQUIRE(*followsSet == EXPECTED_FOLLOWS_SET);
}