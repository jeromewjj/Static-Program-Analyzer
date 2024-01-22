#include "QPS/Clause/WithClause/WithClause.h"
#include "catch.hpp"

TEST_CASE("Test WithClause creation") {
    SECTION("Valid WithClause") {
        SECTION("Basic") {
            std::string attrCond = "a.procName='hello'";
            WithClause testWithClause(attrCond);

            REQUIRE(testWithClause.attrCompare->leftArg.type == ArgType::ATTRREF);
            REQUIRE(testWithClause.attrCompare->leftArg.str == "a.procName");

            REQUIRE(testWithClause.attrCompare->rightArg.type == ArgType::EXPRESSION);
            REQUIRE(testWithClause.attrCompare->rightArg.str == "'hello'");

            REQUIRE_FALSE(testWithClause.isNot);
        }
    }

    SECTION("Invalid WithClause") {
        SECTION("Missing =") {
            std::string attrCond = "a.procName 'hello'";
            REQUIRE_THROWS(WithClause(attrCond));
        }

        SECTION("Invalid not") {
            std::string attrCond = "n a.procName='hello'";
            REQUIRE_THROWS(WithClause(attrCond));
        }
    }
}
