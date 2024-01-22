#include "QPS/Declaration/Declaration.h"
#include "QPS/Evaluator/Entity/Entity.h"
#include "catch.hpp"

TEST_CASE("Declaration Construction and Access") {
    SECTION("Valid Declaration") {
        Declaration declaration = Declaration{EntityType::STATEMENT, "s"};
        REQUIRE(declaration.entityType == EntityType::STATEMENT);
        REQUIRE(declaration.synonym == "s");
    }
}