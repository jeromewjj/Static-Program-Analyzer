#include "PKB/Stores/IfStatementStore.h"
#include "catch.hpp"

TEST_CASE("If Statement Store - Basic Tests") {

    std::shared_ptr<IfStatementStore> ifStatementStore = std::make_shared<IfStatementStore>();

    SECTION("Empty store") {

        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::SYNONYM, "x"}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::WILDCARD, ""}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::WILDCARD, ""}) == false);
    }

    SECTION("Store with one if statement") {

        IfStatementStore::IfSet ifSetOne{{1, "x"}};

        ifStatementStore->setIfStatements(ifSetOne);

        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::SYNONYM, "x"}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::WILDCARD, ""}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::SYNONYM, "x"}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::WILDCARD, ""}) == true);
    }

    SECTION("Store with multiple if statements") {

        IfStatementStore::IfSet ifSetMultiple{{1, "x"}, {1, "y"}, {2, "x"}, {2, "z"}, {2, "a"}, {3, "w"}};

        ifStatementStore->setIfStatements(ifSetMultiple);

        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::SYNONYM, "x"}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::SYNONYM, "y"}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(1, {ArgType::WILDCARD, ""}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::SYNONYM, "x"}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::SYNONYM, "a"}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::SYNONYM, "z"}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::SYNONYM, "b"}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(2, {ArgType::WILDCARD, ""}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(3, {ArgType::SYNONYM, "w"}) == true);
        REQUIRE(ifStatementStore->containsIfPattern(3, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(ifStatementStore->containsIfPattern(3, {ArgType::WILDCARD, ""}) == true);
    }
}