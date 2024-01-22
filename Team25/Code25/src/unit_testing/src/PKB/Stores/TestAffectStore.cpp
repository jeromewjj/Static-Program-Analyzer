#include "PKB/Stores/AffectStore.h"
#include "catch.hpp"

TEST_CASE("Test AffectStore - Affect Relationship") {
    AffectStore affectStore;
    AffectStore::AffectSet affectSet = {{1, 2}, {2, 3}};
    affectStore.setAffectRelationships(affectSet);

    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "1")) ==
            false);
    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "3")) ==
            true);

    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "2")) ==
            true);
    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "3")) ==
            true);
    REQUIRE(affectStore.containAffectRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) ==
            false);

    affectStore.clearAffectStore();
    REQUIRE_FALSE(affectStore.checkAffectGenerated());
    REQUIRE_FALSE(affectStore.containAffectRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")));
}