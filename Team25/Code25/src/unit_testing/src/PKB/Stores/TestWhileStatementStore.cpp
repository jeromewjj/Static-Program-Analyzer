#include "PKB/Stores/WhileStatementStore.h"
#include "catch.hpp"

TEST_CASE("While Statement Store - Basic Tests") {

    std::shared_ptr<WhileStatementStore> whileStatementStore = std::make_shared<WhileStatementStore>();

    SECTION("Empty store") {

        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::SYNONYM, "x"}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::WILDCARD, ""}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::WILDCARD, ""}) == false);
    }

    SECTION("Store with one while statement") {

        WhileStatementStore::WhileSet whileSetOne{{1, "x"}};

        whileStatementStore->setWhileStatements(whileSetOne);

        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::SYNONYM, "x"}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::WILDCARD, ""}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::SYNONYM, "x"}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::WILDCARD, ""}) == true);
    }

    SECTION("Store with multiple while statements") {

        WhileStatementStore::WhileSet whileSetMultiple{{1, "x"}, {1, "y"}, {2, "x"}, {2, "z"}, {2, "a"}, {3, "w"}};

        whileStatementStore->setWhileStatements(whileSetMultiple);

        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::SYNONYM, "x"}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::SYNONYM, "y"}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(1, {ArgType::WILDCARD, ""}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::SYNONYM, "x"}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::SYNONYM, "a"}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::SYNONYM, "z"}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::SYNONYM, "b"}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(2, {ArgType::WILDCARD, ""}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(3, {ArgType::SYNONYM, "w"}) == true);
        REQUIRE(whileStatementStore->containsWhilePattern(3, {ArgType::SYNONYM, "a"}) == false);
        REQUIRE(whileStatementStore->containsWhilePattern(3, {ArgType::WILDCARD, ""}) == true);
    }
}