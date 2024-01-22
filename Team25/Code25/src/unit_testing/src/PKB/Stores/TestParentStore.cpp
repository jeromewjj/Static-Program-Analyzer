#include "PKB/Stores/ParentStore.h"
#include "catch.hpp"

TEST_CASE("ParentStore - Basic Test") {
    std::shared_ptr<ParentStore> parentStore = std::make_shared<ParentStore>();

    SECTION("Test getChilds function") {
        ParentStore::ParentSet parentSet{{1, 2}, {1, 3}, {1, 4}, {5, 1}};

        parentStore->setParentRelationship(parentSet);

        REQUIRE(parentStore->getChilds(1) == ParentStore::StmtSet{2, 3, 4});
        REQUIRE(parentStore->getChilds(5) == ParentStore::StmtSet{1});
    }

    SECTION("Test getChildsStar function") {
        ParentStore::ParentSet parentSet{{1, 2}, {1, 3}, {1, 4}, {5, 1}};

        parentStore->setParentRelationship(parentSet);

        REQUIRE(parentStore->getChildsStar(1) == ParentStore::StmtSet{2, 3, 4});
        REQUIRE(parentStore->getChildsStar(5) == ParentStore::StmtSet{1, 2, 3, 4});
    }

    SECTION("Test getParent function") {
        ParentStore::ParentSet parentSet{{1, 2}, {1, 3}, {1, 4}, {5, 1}};

        parentStore->setParentRelationship(parentSet);

        REQUIRE(parentStore->getParent(2) == 1);
        REQUIRE(parentStore->getParent(1) == 5);
        REQUIRE(parentStore->getParent(4) == 1);
    }

    SECTION("Test getParentsStar function") {
        ParentStore::ParentSet parentSet{{1, 2}, {1, 3}, {1, 4}, {5, 1}};

        parentStore->setParentRelationship(parentSet);

        REQUIRE(parentStore->getParentStar(2) == ParentStore::StmtSet{1, 5});
        REQUIRE(parentStore->getParentStar(1) == ParentStore::StmtSet{5});
        REQUIRE(parentStore->getParentStar(4) == ParentStore::StmtSet{1, 5});
    }
}

TEST_CASE("containParentRelation returns true if follow relation exists") {
    ParentStore parentStore;
    ParentStore::ParentSet parentSet = {{1, 2}, {2, 3}};
    parentStore.setParentRelationship(parentSet);

    REQUIRE(parentStore.containParentRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(parentStore.containParentRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "1")) ==
            false);
    REQUIRE(parentStore.containParentRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(parentStore.containParentRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "3")) ==
            true);

    REQUIRE(parentStore.containParentRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(parentStore.containParentRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(parentStore.containParentRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(parentStore.containParentRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(parentStore.containParentRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(parentStore.containParentRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) ==
            false);
}

TEST_CASE("containParentStarRelation returns true if follow relation exists") {
    ParentStore parentStore;
    ParentStore::ParentSet parentSet = {{1, 2}, {2, 3}};
    parentStore.setParentRelationship(parentSet);

    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "1")) ==
            false);
    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "3")) ==
            true);

    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(parentStore.containParentStarRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) ==
            false);
}
