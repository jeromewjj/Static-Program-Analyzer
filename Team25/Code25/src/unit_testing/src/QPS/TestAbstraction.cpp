#include "QPS/Abstraction/Abstraction.h"
#include "catch.hpp"

TEST_CASE("Test Abstraction creation") {
    REQUIRE_NOTHROW([]() {
        Abstraction a{AbstractionType::PARENTS,
                      {{ArgType::EXPRESSION, "expr"}, {ArgType::WILDCARD, "wild"}, {ArgType::SYNONYM, "haha"}}};
    }());
}