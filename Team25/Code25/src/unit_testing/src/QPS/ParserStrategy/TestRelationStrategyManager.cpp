#include "QPS/ParserStrategy/RelationStrategyManager.h"
#include "catch.hpp"

TEST_CASE("Test parseAbstraction") {
    SECTION("Valid Input") {
        RelationStrategyManager manager;
        std::string rel = "Follows";
        std::string ref1 = "stmtRef1";
        std::string ref2 = "stmtRef2";

        Abstraction abstraction = manager.parseAbstraction(rel, ref1, ref2);

        REQUIRE(abstraction.type == AbstractionType::FOLLOWS);
        REQUIRE(abstraction.args.size() == 2);
    }

    SECTION("Invalid relRef") {
        RelationStrategyManager manager;
        std::string rel = "INVALID";
        std::string ref1 = "stmtRef1";
        std::string ref2 = "stmtRef2";

        REQUIRE_THROWS_WITH(manager.parseAbstraction(rel, ref1, ref2), "Invalid relRef: INVALID");
    }
}
