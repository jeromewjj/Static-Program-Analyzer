#include "PKB/Stores/FollowsStore.h"
#include "catch.hpp"

TEST_CASE("FollowsStore - Basic Test") {
    std::shared_ptr<FollowsStore> followsStore = std::make_shared<FollowsStore>();

    SECTION("Test getFollower function") {
        FollowsStore::FollowsSet followsSet{{1, 2}, {2, 3}, {3, 4}, {4, 5}};

        followsStore->setFollowsRelationships((followsSet));

        REQUIRE(followsStore->getFollower(1) == 2);
        REQUIRE(followsStore->getFollower(2) == 3);
        REQUIRE(followsStore->getFollower(3) == 4);
        REQUIRE(followsStore->getFollower(4) == 5);
    }

    SECTION("Test getFollowerStars function") {
        FollowsStore::FollowsSet followsSet{{1, 2}, {2, 3}, {3, 4}, {4, 5}};

        followsStore->setFollowsRelationships((followsSet));

        REQUIRE(followsStore->getFollowerStars(1) == FollowsStore::StmtSet{2, 3, 4, 5});
        REQUIRE(followsStore->getFollowerStars(2) == FollowsStore::StmtSet{3, 4, 5});
        REQUIRE(followsStore->getFollowerStars(3) == FollowsStore::StmtSet{4, 5});
        REQUIRE(followsStore->getFollowerStars(4) == FollowsStore::StmtSet{5});
    }

    SECTION("Test getFollowee function") {
        FollowsStore::FollowsSet followsSet{{1, 2}, {2, 3}, {3, 4}, {4, 5}};

        followsStore->setFollowsRelationships((followsSet));

        REQUIRE(followsStore->getFollowee(2) == 1);
        REQUIRE(followsStore->getFollowee(3) == 2);
        REQUIRE(followsStore->getFollowee(4) == 3);
        REQUIRE(followsStore->getFollowee(5) == 4);
    }

    SECTION("Test getFolloweeStar function") {
        FollowsStore::FollowsSet followsSet{{1, 2}, {2, 3}, {3, 4}, {4, 5}};

        followsStore->setFollowsRelationships((followsSet));

        REQUIRE(followsStore->getFolloweeStars(2) == FollowsStore::StmtSet{1});
        REQUIRE(followsStore->getFolloweeStars(3) == FollowsStore::StmtSet{1, 2});
        REQUIRE(followsStore->getFolloweeStars(4) == FollowsStore::StmtSet{1, 2, 3});
        REQUIRE(followsStore->getFolloweeStars(5) == FollowsStore::StmtSet{1, 2, 3, 4});
    }
}

TEST_CASE("containFollowsRelation returns true if follow relation exists") {
    FollowsStore followsStore;
    FollowsStore::FollowsSet followsSet = {{1, 2}, {2, 3}};
    followsStore.setFollowsRelationships(followsSet);

    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "1")) ==
            false);
    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "3")) ==
            true);

    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(followsStore.containFollowsRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) ==
            false);
}

TEST_CASE("containFollowsStarRelation returns true if follow star relation exists") {
    FollowsStore followsStore;
    FollowsStore::FollowsSet followsSet = {{1, 2}, {2, 3}};
    followsStore.setFollowsRelationships(followsSet);

    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "1")) ==
            false);
    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "3")) ==
            true);

    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(followsStore.containFollowsStarRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) ==
            false);
}
