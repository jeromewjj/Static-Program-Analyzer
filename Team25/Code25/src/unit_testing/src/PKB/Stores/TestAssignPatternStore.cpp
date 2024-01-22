#include "PKB/Stores/AssignPatternStore.h"
#include "catch.hpp"

TEST_CASE("AssignPatternStore - Basic Test Old") {
    std::shared_ptr<AssignPatternStore> assignPatternStore = std::make_shared<AssignPatternStore>();
    Assign assign1 = {1, "a", "((x)+(y))", {"((x)+(y))", "(x)", "(y)"}};
    Assign assign2 = {2, "b", "(y)", {"(y)"}};
    Assign assign3 = {3, "b", "(1)", {"(1)"}};

    AssignPatternStore::AssignSet assignSet = {assign1, assign2, assign3};

    assignPatternStore->setAssignPatterns(assignSet);

    SECTION(
        "Test containAssignPattern function with First Argument as Variable and Second Argument as Exact Expression") {
        // Check all assign is available
        REQUIRE(
            assignPatternStore->containAssignPattern(1, {ArgType::SYNONYM, "a"}, {ArgType::EXPRESSION, "((x)+(y))"}));
        REQUIRE(assignPatternStore->containAssignPattern(2, {ArgType::SYNONYM, "b"}, {ArgType::EXPRESSION, "(y)"}));
        REQUIRE(assignPatternStore->containAssignPattern(3, {ArgType::SYNONYM, "b"}, {ArgType::EXPRESSION, "(1)"}));

        // Check assign not available
        REQUIRE_FALSE(
            assignPatternStore->containAssignPattern(1, {ArgType::SYNONYM, "b"}, {ArgType::EXPRESSION, "((x)+(y))"}));
        REQUIRE_FALSE(
            assignPatternStore->containAssignPattern(2, {ArgType::SYNONYM, "b"}, {ArgType::EXPRESSION, "((x)+(y))"}));
        REQUIRE_FALSE(
            assignPatternStore->containAssignPattern(4, {ArgType::SYNONYM, "b"}, {ArgType::EXPRESSION, "(1)"}));
    }

    SECTION("Test containAssignPattern function with First Argument as Variable and Second Argument as Partial "
            "Expression") {
        // Check all assign is available
        REQUIRE(assignPatternStore->containAssignPattern(1, {ArgType::SYNONYM, "a"}, {ArgType::WILDCARD_EXPR, "(x)"}));
        REQUIRE(assignPatternStore->containAssignPattern(2, {ArgType::SYNONYM, "b"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(assignPatternStore->containAssignPattern(3, {ArgType::SYNONYM, "b"}, {ArgType::WILDCARD_EXPR, "(1)"}));
    }

    SECTION(
        "Test containAssignPattern function with First Argument as Wild Card and Second Argument as Exact Expression") {
        // Check all assign is available
        REQUIRE(
            assignPatternStore->containAssignPattern(1, {ArgType::WILDCARD, ""}, {ArgType::EXPRESSION, "((x)+(y))"}));
        REQUIRE(assignPatternStore->containAssignPattern(2, {ArgType::WILDCARD, ""}, {ArgType::EXPRESSION, "(y)"}));
        REQUIRE(assignPatternStore->containAssignPattern(3, {ArgType::WILDCARD, ""}, {ArgType::EXPRESSION, "(1)"}));

        // Check assign not available
        REQUIRE_FALSE(
            assignPatternStore->containAssignPattern(1, {ArgType::WILDCARD, ""}, {ArgType::EXPRESSION, "(x)"}));
        REQUIRE_FALSE(
            assignPatternStore->containAssignPattern(2, {ArgType::WILDCARD, ""}, {ArgType::EXPRESSION, "((x)+(y))"}));
        REQUIRE_FALSE(
            assignPatternStore->containAssignPattern(4, {ArgType::WILDCARD, ""}, {ArgType::EXPRESSION, "(1)"}));
    }

    SECTION("Test containAssignPattern function with First Argument as Wild Card and Second Argument as Wild Card") {
        // Check all assign is available
        REQUIRE(assignPatternStore->containAssignPattern(1, {ArgType::WILDCARD, ""}, {ArgType::WILDCARD, ""}));
        REQUIRE(assignPatternStore->containAssignPattern(2, {ArgType::WILDCARD, ""}, {ArgType::WILDCARD, ""}));
        REQUIRE(assignPatternStore->containAssignPattern(3, {ArgType::WILDCARD, ""}, {ArgType::WILDCARD, ""}));

        // Check assign not available
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(4, {ArgType::WILDCARD, ""}, {ArgType::WILDCARD, ""}));
    }
}

TEST_CASE("AssignPatternStore - Basic Test") {
    std::shared_ptr<AssignPatternStore> assignPatternStore = std::make_shared<AssignPatternStore>();
    Assign assign1 = {1, "a", "((x)+(y))", {"((x)+(y))", "(x)", "(y)"}};
    Assign assign2 = {2, "b", "(y)", {"(y)"}};
    Assign assign3 = {3, "b", "(1)", {"(1)"}};

    AssignPatternStore::AssignSet assignSet = {assign1, assign2, assign3};

    assignPatternStore->setAssignPatterns(assignSet);

    SECTION(
        "Test containAssignPattern function with First Argument as Variable and Second Argument as Exact Expression") {
        // Check all assign is available
        REQUIRE(assignPatternStore->containAssignPattern(1, Argument(ArgType::SYNONYM, "a"),
                                                         Argument(ArgType::EXPRESSION, "((x)+(y))")));
        REQUIRE(assignPatternStore->containAssignPattern(2, Argument(ArgType::SYNONYM, "b"),
                                                         Argument(ArgType::EXPRESSION, "(y)")));
        REQUIRE(assignPatternStore->containAssignPattern(3, Argument(ArgType::SYNONYM, "b"),
                                                         Argument(ArgType::EXPRESSION, "(1)")));
        // Check assign not available
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(1, Argument(ArgType::SYNONYM, "b"),
                                                               Argument(ArgType::EXPRESSION, "((x)+(y))")));
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(2, Argument(ArgType::SYNONYM, "b"),
                                                               Argument(ArgType::EXPRESSION, "((x)+(y))")));
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(4, Argument(ArgType::SYNONYM, "b"),
                                                               Argument(ArgType::EXPRESSION, "(1)")));
    }

    SECTION("Test containAssignPattern function with First Argument as Variable and Second Argument as Partial "
            "Expression") {
        // Check all assign is available
        REQUIRE(assignPatternStore->containAssignPattern(1, Argument(ArgType::SYNONYM, "a"),
                                                         Argument(ArgType::WILDCARD_EXPR, "(x)")));
        REQUIRE(assignPatternStore->containAssignPattern(2, Argument(ArgType::SYNONYM, "b"),
                                                         Argument(ArgType::WILDCARD_EXPR, "(y)")));
        REQUIRE(assignPatternStore->containAssignPattern(3, Argument(ArgType::SYNONYM, "b"),
                                                         Argument(ArgType::WILDCARD_EXPR, "(1)")));
    }

    SECTION(
        "Test containAssignPattern function with First Argument as Wild Card and Second Argument as Exact Expression") {
        // Check all assign is available
        REQUIRE(assignPatternStore->containAssignPattern(1, Argument(ArgType::WILDCARD, ""),
                                                         Argument(ArgType::EXPRESSION, "((x)+(y))")));
        REQUIRE(assignPatternStore->containAssignPattern(2, Argument(ArgType::WILDCARD, ""),
                                                         Argument(ArgType::EXPRESSION, "(y)")));
        REQUIRE(assignPatternStore->containAssignPattern(3, Argument(ArgType::WILDCARD, ""),
                                                         Argument(ArgType::EXPRESSION, "(1)")));

        // Check assign not available
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(1, Argument(ArgType::WILDCARD, ""),
                                                               Argument(ArgType::EXPRESSION, "(x)")));
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(2, Argument(ArgType::WILDCARD, ""),
                                                               Argument(ArgType::EXPRESSION, "((x)+(y))")));
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(4, Argument(ArgType::WILDCARD, ""),
                                                               Argument(ArgType::EXPRESSION, "(1)")));
    }

    SECTION("Test containAssignPattern function with First Argument as Wild Card and Second Argument as Wild Card") {
        // Check all assign is available
        REQUIRE(assignPatternStore->containAssignPattern(1, Argument(ArgType::WILDCARD, ""),
                                                         Argument(ArgType::WILDCARD, "")));
        REQUIRE(assignPatternStore->containAssignPattern(2, Argument(ArgType::WILDCARD, ""),
                                                         Argument(ArgType::WILDCARD, "")));
        REQUIRE(assignPatternStore->containAssignPattern(3, Argument(ArgType::WILDCARD, ""),
                                                         Argument(ArgType::WILDCARD, "")));

        // Check assign not available
        REQUIRE_FALSE(assignPatternStore->containAssignPattern(4, Argument(ArgType::WILDCARD, ""),
                                                               Argument(ArgType::WILDCARD, "")));
    }
}
