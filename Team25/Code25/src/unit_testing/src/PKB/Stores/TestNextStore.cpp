#include "PKB/Stores/NextStore.h"
#include "catch.hpp"

TEST_CASE("Test NextStore - Next Relationship") {
    NextStore nextStore;
    NextStore::NextSet nextSet = {{1, 2}, {2, 3}};
    nextStore.setNextRelationships(nextSet);

    REQUIRE(nextStore.containNextRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) == true);

    REQUIRE(nextStore.containNextRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "1")) == false);
    REQUIRE(nextStore.containNextRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "2")) == true);
    REQUIRE(nextStore.containNextRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "3")) == true);

    REQUIRE(nextStore.containNextRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(nextStore.containNextRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(nextStore.containNextRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) == false);

    REQUIRE(nextStore.containNextRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "2")) == true);
    REQUIRE(nextStore.containNextRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "3")) == true);
    REQUIRE(nextStore.containNextRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) == false);
}

TEST_CASE("Test NextStore - Next Star Relationship") {
    NextStore nextStore;
    NextStore::NextSet nextSet = {{1, 2}, {2, 3}};
    nextStore.setNextRelationships(nextSet);

    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "1")) ==
            false);
    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "3")) ==
            true);

    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(nextStore.containNextStarRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) ==
            false);
}
