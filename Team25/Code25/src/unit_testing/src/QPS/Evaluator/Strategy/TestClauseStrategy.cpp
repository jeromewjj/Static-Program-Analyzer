#include "../../Mocks.h"
#include "QPS/Evaluator/Action/Strategy/ClauseStrategy.h"
#include "catch.hpp"

TEST_CASE("Test STStrategy") {
    PKB pkb;
    Mock::MockPKBReader reader{pkb};

    SECTION("Test Follows/Follows star Abstraction") {
        Context context;
        context.synonymPos["s"] = Entity{"", 1, EntityType::STATEMENT};
        context.synonymPos["s1"] = Entity{"", 2, EntityType::ASSIGN};
        context.synonymPos["s2"] = Entity{"", 7, EntityType::ASSIGN};
        {
            Argument arg1{ArgType::SYNONYM, "s"};
            Argument arg2{ArgType::WILDCARD, ""};
            Abstraction abs{AbstractionType::FOLLOWS, {arg1, arg2}};
            STStrategy strategy{abs};
            REQUIRE(strategy.execute(reader, context));

            Argument arg3{ArgType::SYNONYM, "s1"};
            Abstraction abs1{AbstractionType::FOLLOWS, {arg1, arg3}};
            STStrategy strategy1{abs1};
            REQUIRE(strategy1.execute(reader, context));

            Argument arg4{ArgType::SYNONYM, "s2"};
            Abstraction abs2{AbstractionType::FOLLOWS, {arg1, arg4}};
            STStrategy strategy2{abs2};
            REQUIRE_FALSE(strategy2.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "s"};
            Argument arg2{ArgType::WILDCARD, ""};
            Abstraction abs{AbstractionType::FOLLOWS_T, {arg1, arg2}};
            STStrategy strategy{abs};
            REQUIRE(strategy.execute(reader, context));

            Argument arg3{ArgType::SYNONYM, "s1"};
            Abstraction abs1{AbstractionType::FOLLOWS_T, {arg1, arg3}};
            STStrategy strategy1{abs1};
            REQUIRE(strategy1.execute(reader, context));

            Argument arg4{ArgType::SYNONYM, "s2"};
            Abstraction abs2{AbstractionType::FOLLOWS_T, {arg1, arg4}};
            STStrategy strategy2{abs2};
            REQUIRE_FALSE(strategy2.execute(reader, context));
        }
    }

    SECTION("Test Parents/Parents star Abstraction") {
        Context context;
        context.synonymPos["s"] = Entity{"", 5, EntityType::STATEMENT};
        context.synonymPos["s1"] = Entity{"", 6, EntityType::ASSIGN};
        context.synonymPos["s2"] = Entity{"", 3, EntityType::ASSIGN};
        {
            Argument arg1{ArgType::SYNONYM, "s"};
            Argument arg2{ArgType::WILDCARD, ""};
            Abstraction abs{AbstractionType::PARENTS, {arg1, arg2}};
            STStrategy strategy{abs};
            REQUIRE(strategy.execute(reader, context));

            Argument arg3{ArgType::SYNONYM, "s1"};
            Abstraction abs1{AbstractionType::PARENTS, {arg1, arg3}};
            STStrategy strategy1{abs1};
            REQUIRE(strategy1.execute(reader, context));

            Argument arg4{ArgType::SYNONYM, "s2"};
            Abstraction abs2{AbstractionType::PARENTS, {arg1, arg4}};
            STStrategy strategy2{abs2};
            REQUIRE_FALSE(strategy2.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "s"};
            Argument arg2{ArgType::WILDCARD, ""};
            Abstraction abs{AbstractionType::PARENTS_T, {arg1, arg2}};
            STStrategy strategy{abs};
            REQUIRE(strategy.execute(reader, context));

            Argument arg3{ArgType::SYNONYM, "s1"};
            Abstraction abs1{AbstractionType::PARENTS_T, {arg1, arg3}};
            STStrategy strategy1{abs1};
            REQUIRE(strategy1.execute(reader, context));

            Argument arg4{ArgType::SYNONYM, "s2"};
            Abstraction abs2{AbstractionType::PARENTS_T, {arg1, arg4}};
            STStrategy strategy2{abs2};
            REQUIRE_FALSE(strategy2.execute(reader, context));
        }
    }

    SECTION("Test Uses Abstraction") {
        Context context;
        context.synonymPos["s"] = Entity{"", 2, EntityType::STATEMENT};
        context.synonymPos["v"] = Entity{"v_x", 0, EntityType::VARIABLE};
        context.synonymPos["v1"] = Entity{"v_y", 3, EntityType::ASSIGN};

        Argument arg1{ArgType::SYNONYM, "s"};
        Argument arg2{ArgType::WILDCARD, ""};
        Abstraction abs{AbstractionType::USES, {arg1, arg2}};
        STStrategy strategy{abs};
        REQUIRE(strategy.execute(reader, context));

        Argument arg3{ArgType::SYNONYM, "v"};
        Abstraction abs1{AbstractionType::USES, {arg1, arg3}};
        STStrategy strategy1{abs1};
        REQUIRE(strategy1.execute(reader, context));

        Argument arg4{ArgType::SYNONYM, "pr"};
        Abstraction abs2{AbstractionType::USES, {arg4, arg3}};
        STStrategy strategy2{abs1};
        REQUIRE(strategy2.execute(reader, context));

        Argument arg5{ArgType::SYNONYM, "v1"};
        Abstraction abs3{AbstractionType::USES, {arg1, arg5}};
        STStrategy strategy3{abs3};
        REQUIRE_FALSE(strategy3.execute(reader, context));
    }

    SECTION("Test Modifies Abstraction") {
        Context context;
        context.synonymPos["s"] = Entity{"", 2, EntityType::STATEMENT};
        context.synonymPos["pr"] = Entity{"p_x", 0, EntityType::PROCEDURE};
        context.synonymPos["v"] = Entity{"v_z", 0, EntityType::VARIABLE};
        context.synonymPos["v1"] = Entity{"v_x", 0, EntityType::VARIABLE};

        Argument arg1{ArgType::SYNONYM, "s"};
        Argument arg2{ArgType::WILDCARD, ""};
        Abstraction abs{AbstractionType::MODIFIES, {arg1, arg2}};
        STStrategy strategy{abs};
        REQUIRE(strategy.execute(reader, context));

        Argument arg3{ArgType::SYNONYM, "v"};
        Abstraction abs1{AbstractionType::MODIFIES, {arg1, arg3}};
        STStrategy strategy1{abs1};
        REQUIRE(strategy1.execute(reader, context));

        Argument arg4{ArgType::SYNONYM, "pr"};
        Abstraction abs2{AbstractionType::MODIFIES, {arg4, arg3}};
        STStrategy strategy2{abs1};
        REQUIRE(strategy2.execute(reader, context));

        Argument arg5{ArgType::SYNONYM, "v1"};
        Abstraction abs3{AbstractionType::MODIFIES, {arg1, arg5}};
        STStrategy strategy3{abs3};
        REQUIRE_FALSE(strategy3.execute(reader, context));
    }

    SECTION("Test Next/Next star Abstraction") {
        Context context;
        context.synonymPos["s"] = Entity{"", 1, EntityType::STATEMENT};
        context.synonymPos["s1"] = Entity{"", 2, EntityType::ASSIGN};
        context.synonymPos["s2"] = Entity{"", 7, EntityType::ASSIGN};
        {
            Argument arg1{ArgType::SYNONYM, "s"};
            Argument arg2{ArgType::WILDCARD, ""};
            Abstraction abs{AbstractionType::NEXT, {arg1, arg2}};
            STStrategy strategy{abs};
            REQUIRE(strategy.execute(reader, context));

            Argument arg3{ArgType::SYNONYM, "s1"};
            Abstraction abs1{AbstractionType::NEXT, {arg1, arg3}};
            STStrategy strategy1{abs1};
            REQUIRE(strategy1.execute(reader, context));

            Argument arg4{ArgType::SYNONYM, "s2"};
            Abstraction abs2{AbstractionType::NEXT, {arg1, arg4}};
            STStrategy strategy2{abs2};
            REQUIRE_FALSE(strategy2.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "s"};
            Argument arg2{ArgType::WILDCARD, ""};
            Abstraction abs{AbstractionType::NEXT_T, {arg1, arg2}};
            STStrategy strategy{abs};
            REQUIRE(strategy.execute(reader, context));

            Argument arg3{ArgType::SYNONYM, "s1"};
            Abstraction abs1{AbstractionType::NEXT_T, {arg1, arg3}};
            STStrategy strategy1{abs1};
            REQUIRE(strategy1.execute(reader, context));

            Argument arg4{ArgType::SYNONYM, "s2"};
            Abstraction abs2{AbstractionType::NEXT_T, {arg1, arg4}};
            STStrategy strategy2{abs2};
            REQUIRE_FALSE(strategy2.execute(reader, context));
        }
    }

    SECTION("Test Affects Abstraction") {
        Context context;
        context.synonymPos["s"] = Entity{"", 5, EntityType::STATEMENT};
        context.synonymPos["s1"] = Entity{"", 6, EntityType::ASSIGN};
        context.synonymPos["s2"] = Entity{"", 3, EntityType::ASSIGN};
        {
            Argument arg1{ArgType::SYNONYM, "s"};
            Argument arg2{ArgType::WILDCARD, ""};
            Abstraction abs{AbstractionType::AFFECTS, {arg1, arg2}};
            STStrategy strategy{abs};
            REQUIRE(strategy.execute(reader, context));

            Argument arg3{ArgType::SYNONYM, "s1"};
            Abstraction abs1{AbstractionType::AFFECTS, {arg1, arg3}};
            STStrategy strategy1{abs1};
            REQUIRE(strategy1.execute(reader, context));

            Argument arg4{ArgType::SYNONYM, "s2"};
            Abstraction abs2{AbstractionType::AFFECTS, {arg1, arg4}};
            STStrategy strategy2{abs2};
            REQUIRE_FALSE(strategy2.execute(reader, context));
        }
    }
}

TEST_CASE("Test PatStrategy") {
    PKB pkb;
    Mock::MockPKBReader reader{pkb};

    SECTION("Test Assign Pattern") {
        Context context;
        context.synonymPos["a"] = Entity{"", 7, EntityType::ASSIGN};
        context.synonymPos["a1"] = Entity{"", 2, EntityType::ASSIGN};
        context.synonymPos["a2"] = Entity{"", 6, EntityType::ASSIGN};
        context.synonymPos["v"] = Entity{"v_y", 0, EntityType::VARIABLE};

        {
            Argument arg1{ArgType::WILDCARD, ""};
            Argument arg2{ArgType::WILDCARD, ""};
            PatStrategy strategy{"a", {arg1, arg2}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            Argument arg2{ArgType::WILDCARD, ""};
            PatStrategy strategy{"a", {arg1, arg2}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            Argument arg2{ArgType::EXPRESSION, "\"((v_x)+(v_y))\""};
            PatStrategy strategy{"a", {arg1, arg2}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            Argument arg2{ArgType::WILDCARD_EXPR, "_\"(v_y)\"_"};
            PatStrategy strategy{"a", {arg1, arg2}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::WILDCARD, ""};
            Argument arg2{ArgType::WILDCARD, ""};
            PatStrategy strategy{"a1", {arg1, arg2}};

            REQUIRE_FALSE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            Argument arg2{ArgType::WILDCARD, ""};
            PatStrategy strategy{"a2", {arg1, arg2}};

            REQUIRE_FALSE(strategy.execute(reader, context));
        }
    }

    SECTION("Test If Pattern") {
        Context context;
        context.synonymPos["if"] = Entity{"", 12, EntityType::IF};
        context.synonymPos["if1"] = Entity{"", 13, EntityType::IF};
        context.synonymPos["v"] = Entity{"v_y", 0, EntityType::VARIABLE};

        {
            Argument arg1{ArgType::WILDCARD, ""};
            PatStrategy strategy{"if", {arg1}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            PatStrategy strategy{"if", {arg1}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            PatStrategy strategy{"if1", {arg1}};

            REQUIRE_FALSE(strategy.execute(reader, context));
        }
    }

    SECTION("Test While Pattern") {
        Context context;
        context.synonymPos["w"] = Entity{"", 10, EntityType::WHILE};
        context.synonymPos["w1"] = Entity{"", 13, EntityType::WHILE};
        context.synonymPos["v"] = Entity{"v_x", 0, EntityType::VARIABLE};

        {
            Argument arg1{ArgType::WILDCARD, ""};
            PatStrategy strategy{"w", {arg1}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            PatStrategy strategy{"w", {arg1}};

            REQUIRE(strategy.execute(reader, context));
        }

        {
            Argument arg1{ArgType::SYNONYM, "v"};
            PatStrategy strategy{"w1", {arg1}};

            REQUIRE_FALSE(strategy.execute(reader, context));
        }
    }
}

TEST_CASE("Test WithStrategy") {
    PKB pkb;
    Mock::MockPKBReader reader{pkb};

    SECTION("Test basic default values") {

        {
            Context context;
            context.synonymPos["s"] = {"", 5, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.stmt#"};
            Argument arg2{ArgType::ATTRREF, "s.stmt#"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"", 5, EntityType::STATEMENT};
            context.synonymPos["s1"] = {"", 5, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.stmt#"};
            Argument arg2{ArgType::ATTRREF, "s1.stmt#"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"", 5, EntityType::STATEMENT};
            context.synonymPos["s1"] = {"", 6, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.stmt#"};
            Argument arg2{ArgType::ATTRREF, "s1.stmt#"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE_FALSE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["v"] = {"v_x", 0, EntityType::VARIABLE};
            context.synonymPos["v1"] = {"v_x", 0, EntityType::VARIABLE};

            Argument arg1{ArgType::ATTRREF, "v.varName"};
            Argument arg2{ArgType::ATTRREF, "v1.varName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["v"] = {"v_x", 0, EntityType::VARIABLE};
            context.synonymPos["v1"] = {"v_y", 0, EntityType::VARIABLE};

            Argument arg1{ArgType::ATTRREF, "v.varName"};
            Argument arg2{ArgType::ATTRREF, "v1.varName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE_FALSE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["c"] = {"", 3, EntityType::CONSTANT};
            context.synonymPos["c1"] = {"", 3, EntityType::CONSTANT};

            Argument arg1{ArgType::ATTRREF, "c.value"};
            Argument arg2{ArgType::ATTRREF, "c1.value"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["p"] = {"p_x", 0, EntityType::PROCEDURE};
            context.synonymPos["p1"] = {"p_x", 0, EntityType::PROCEDURE};

            Argument arg1{ArgType::ATTRREF, "p.procName"};
            Argument arg2{ArgType::ATTRREF, "p1.procName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }
    }

    SECTION("Test PKB calls") {

        {
            Context context;
            context.synonymPos["s"] = {"", 3, EntityType::CALL};
            context.synonymPos["s1"] = {"", 3, EntityType::CALL};

            Argument arg1{ArgType::ATTRREF, "s.procName"};
            Argument arg2{ArgType::ATTRREF, "s1.procName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"", 1, EntityType::CALL};
            context.synonymPos["s1"] = {"", 2, EntityType::CALL};

            Argument arg1{ArgType::ATTRREF, "s.procName"};
            Argument arg2{ArgType::ATTRREF, "s1.procName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"", 1, EntityType::CALL};
            context.synonymPos["s1"] = {"", 3, EntityType::CALL};

            Argument arg1{ArgType::ATTRREF, "s.procName"};
            Argument arg2{ArgType::ATTRREF, "s1.procName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE_FALSE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"", 5, EntityType::STATEMENT};
            context.synonymPos["s1"] = {"", 4, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.varName"};
            Argument arg2{ArgType::ATTRREF, "s1.varName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"", 5, EntityType::PRINT};
            context.synonymPos["s1"] = {"", 4, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.varName"};
            Argument arg2{ArgType::ATTRREF, "s1.varName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"v_y", 0, EntityType::VARIABLE};
            context.synonymPos["s1"] = {"", 4, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.varName"};
            Argument arg2{ArgType::ATTRREF, "s1.varName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"p_x", 0, EntityType::VARIABLE};
            context.synonymPos["s1"] = {"", 2, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.varName"};
            Argument arg2{ArgType::ATTRREF, "s1.procName"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }
    }

    SECTION("Test with constant & expression") {

        {
            Context context;

            Argument arg1{ArgType::EXPRESSION, "'p_x'"};
            Argument arg2{ArgType::EXPRESSION, "'p_x'"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;

            Argument arg1{ArgType::CONSTANT, "5"};
            Argument arg2{ArgType::CONSTANT, "5"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"p_x", 0, EntityType::VARIABLE};

            Argument arg1{ArgType::ATTRREF, "s.varName"};
            Argument arg2{ArgType::EXPRESSION, "'p_x'"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }

        {
            Context context;
            context.synonymPos["s"] = {"", 3, EntityType::STATEMENT};

            Argument arg1{ArgType::ATTRREF, "s.stmt#"};
            Argument arg2{ArgType::CONSTANT, "3"};
            WithStrategy strategy{arg1, arg2};
            REQUIRE(strategy.execute(reader, context));
        }
    }
}
