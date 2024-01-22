#include "QPS/Argument/Argument.h"
#include "catch.hpp"

TEST_CASE("Test arguments equality") {
    SECTION("Test argument equality") {
        Argument a1{ArgType::SYNONYM, "s"};
        Argument a2{ArgType::SYNONYM, "s"};
        REQUIRE(a1 == a2);
    }

    SECTION("Test argument inequality (string)") {
        Argument a1{ArgType::SYNONYM, "s"};
        Argument a2{ArgType::SYNONYM, "a"};
        REQUIRE_FALSE(a1 == a2);
    }

    SECTION("Test argument inequality (type)") {
        Argument a1{ArgType::SYNONYM, "s"};
        Argument a2{ArgType::WILDCARD_EXPR, "s"};
        REQUIRE_FALSE(a1 == a2);
    }

    SECTION("Test wildcard argument equality") {
        Argument a1{ArgType::WILDCARD, "s"};
        // same argument
        Argument a2{ArgType::WILDCARD, "s"};
        // same type, diff str
        Argument a3{ArgType::WILDCARD, "t"};
        // sam str, diff str
        Argument a4{ArgType::EXPRESSION, "s"};
        REQUIRE(a1 == a2);
        REQUIRE(a1 == a3);
        REQUIRE_FALSE(a1 == a4);
    }
}