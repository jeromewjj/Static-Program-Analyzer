#include "QPS/Argument/Argument.h"
#include "QPS/ParserStrategy/RelationStrategy/FollowsStrategy.h"
#include "catch.hpp"

FollowsStrategy followsStrategy;

TEST_CASE("Testing FollowsStrategy parseArgs") {
    SECTION("Valid Follows") {
        std::string ref1 = "stmtRef1";
        std::string ref2 = "stmtRef2";

        std::vector<Argument> result = followsStrategy.parseArgs(ref1, ref2);

        REQUIRE(result.size() == 2);
        REQUIRE(result[0].type == ArgType::SYNONYM);
        REQUIRE(result[0].str == ref1);
        REQUIRE(result[1].type == ArgType::SYNONYM);
        REQUIRE(result[1].str == ref2);
    }

    SECTION("Invalid first ref") {
        std::string ref1 = "\"helloThere\"";
        std::string ref2 = "2";

        REQUIRE_THROWS_WITH(followsStrategy.parseArgs(ref1, ref2), "Invalid stmtRef for Follows: ");
    }

    SECTION("Invalid second ref") {
        std::string ref1 = "1";
        std::string ref2 = "\"helloThere\"";

        REQUIRE_THROWS_WITH(followsStrategy.parseArgs(ref1, ref2), "Invalid stmtRef for Follows: ");
    }

    SECTION("Invalid both ref") {
        std::string ref1 = "\"helloThere\"";
        std::string ref2 = "\"helloThere\"";

        REQUIRE_THROWS_WITH(followsStrategy.parseArgs(ref1, ref2), "Invalid stmtRef for Follows: ");
    }
}