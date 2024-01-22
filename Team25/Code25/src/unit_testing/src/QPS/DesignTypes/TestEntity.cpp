#include "QPS/Evaluator/Entity/Entity.h"
#include "catch.hpp"

TEST_CASE("test entity") {
    SECTION("entity equal") {
        Entity e1 = {"s", 34, EntityType::STATEMENT};
        Entity e2 = {"s", 34, EntityType::STATEMENT};
        REQUIRE(e1 == e2);
    }
    SECTION("entity unequal string") {
        Entity e1 = {"s", 34, EntityType::STATEMENT};
        Entity e2 = {"t", 34, EntityType::STATEMENT};
        REQUIRE_FALSE(e1 == e2);
    }
    SECTION("entity unequal int") {
        Entity e1 = {"s", 34, EntityType::STATEMENT};
        Entity e2 = {"s", 3, EntityType::STATEMENT};
        REQUIRE_FALSE(e1 == e2);
    }
    SECTION("entity unequal entity type") {
        Entity e1 = {"s", 34, EntityType::STATEMENT};
        Entity e2 = {"s", 34, EntityType::ASSIGN};
        REQUIRE_FALSE(e1 == e2);
    }
}

TEST_CASE("test statement entity check") {
    Entity e2{"a", 0, EntityType::STATEMENT};
    Entity e3{"a", 0, EntityType::ASSIGN};
    Entity e4{"a", 0, EntityType::CALL};
    Entity e5{"a", 0, EntityType::PRINT};
    Entity e6{"a", 0, EntityType::READ};
    Entity e7{"a", 0, EntityType::IF};
    Entity e8{"a", 0, EntityType::WHILE};

    {
        Entity entities[]{e2, e3, e4, e5, e6, e7, e8};
        for (const auto& e : entities) {
            REQUIRE(isStatementEntity(e));
        }
    }

    Entity e9{"a", 0, EntityType::VARIABLE};
    Entity e10{"a", 0, EntityType::CONSTANT};
    Entity e1{"a", 0, EntityType::PROCEDURE};
    {
        Entity entities[]{e9, e10, e1};
        for (const auto& e : entities) {
            REQUIRE_FALSE(isStatementEntity(e));
        }
    }
}