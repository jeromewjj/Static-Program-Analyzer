#include "../Mocks.h"
#include "QPS/Argument/Tuple.h"
#include "QPS/Validator/Rulebook.h"
#include "catch.hpp"

TEST_CASE("Test Rulebook") {
    auto declarations = Mock::Declarations();

    SECTION("Test testDeclaration") {
        REQUIRE_NOTHROW(Rulebook::testDeclaration(declarations));

        {
            declarations.push_back({EntityType::VARIABLE, "s"});
            REQUIRE_THROWS(Rulebook::testDeclaration(declarations));
            declarations.pop_back();
        }

        REQUIRE_NOTHROW(Rulebook::testDeclaration(declarations));
    }

    Rulebook rulebook{declarations};

    SECTION("Test testSelClause") {
        auto s = std::make_shared<Argument>(ArgType::SYNONYM, "s");
        auto s1 = std::make_shared<Argument>(ArgType::SYNONYM, "s1");
        auto sss = std::make_shared<Argument>(ArgType::SYNONYM, "sss");
        auto c = std::make_shared<Argument>(ArgType::ATTRREF, "c.procName");
        auto v = std::make_shared<Argument>(ArgType::ATTRREF, "v.stmt#");
        {
            SelClause selClause(s);
            REQUIRE_NOTHROW(rulebook.testSelClause(selClause));
        }

        {
            std::vector<Argument> args{*s, *s1};
            auto tup = std::make_shared<Tuple>(args, "");
            SelClause selClause(tup);
            REQUIRE_NOTHROW(rulebook.testSelClause(selClause));
        }

        {
            std::vector<Argument> args{*s, *sss};
            auto tup = std::make_shared<Tuple>(args, "");
            SelClause selClause(tup);
            REQUIRE_THROWS(rulebook.testSelClause(selClause));
        }

        {
            SelClause selClause(c);
            REQUIRE_NOTHROW(rulebook.testSelClause(selClause));
        }

        {
            SelClause selClause(v);
            REQUIRE_THROWS(rulebook.testSelClause(selClause));
        }

        {
            std::vector<Argument> args{*s, *s1, *c};
            auto tup = std::make_shared<Tuple>(args, "");
            SelClause selClause(tup);
            REQUIRE_NOTHROW(rulebook.testSelClause(selClause));
        }

        {
            std::vector<Argument> args{*s, *s1, *v};
            auto tup = std::make_shared<Tuple>(args, "");
            SelClause selClause(tup);
            REQUIRE_THROWS(rulebook.testSelClause(selClause));
        }
    }

    SECTION("Test testSTClause") {
        Argument arg1{ArgType::SYNONYM, "s"};
        Argument arg2{ArgType::SYNONYM, "s1"};
        Argument arg3{ArgType::SYNONYM, "v"};
        Argument arg4{ArgType::WILDCARD, ""};
        Argument arg5{ArgType::SYNONYM, "sss"};

        {
            Abstraction abs{AbstractionType::FOLLOWS, {arg1, arg2}};
            REQUIRE_NOTHROW(rulebook.testSTClause(abs));
        }

        {
            Abstraction abs{AbstractionType::FOLLOWS, {arg1, arg3}};
            REQUIRE_THROWS(rulebook.testSTClause(abs));
        }

        {
            Abstraction abs{AbstractionType::FOLLOWS, {arg1, arg5}};
            REQUIRE_THROWS(rulebook.testSTClause(abs));
        }

        {
            Abstraction abs{AbstractionType::FOLLOWS, {arg1, arg4}};
            REQUIRE_NOTHROW(rulebook.testSTClause(abs));
        }

        {
            Abstraction abs{AbstractionType::FOLLOWS, {arg1, arg4}};
            REQUIRE_NOTHROW(rulebook.testSTClause(abs));
        }

        {
            Abstraction abs{AbstractionType::MODIFIES, {arg4, arg3}};
            REQUIRE_THROWS(rulebook.testSTClause(abs));
        }
    }

    SECTION("Test testPatClause") {
        Argument arg1{ArgType::SYNONYM, "a"};
        Argument arg2{ArgType::SYNONYM, "s"};
        Argument arg3{ArgType::SYNONYM, "v"};
        Argument arg4{ArgType::WILDCARD, ""};
        Argument arg5{ArgType::SYNONYM, "sss"};

        { REQUIRE_NOTHROW(rulebook.testPatClause({arg1, arg3})); }

        { REQUIRE_NOTHROW(rulebook.testPatClause({arg1, arg3, arg2})); }

        { REQUIRE_THROWS(rulebook.testPatClause({arg1, arg2})); }

        { REQUIRE_NOTHROW(rulebook.testPatClause({arg1, arg4})); }

        { REQUIRE_THROWS(rulebook.testPatClause({arg1, arg4, arg5})); }
    }

    SECTION("Test testWithClause") {
        REQUIRE_NOTHROW(rulebook.testWithClause({{ArgType::CONSTANT, "1"}, {ArgType::CONSTANT, "1"}}));
        REQUIRE_NOTHROW(rulebook.testWithClause({{ArgType::EXPRESSION, "1"}, {ArgType::EXPRESSION, "1"}}));
        REQUIRE_NOTHROW(rulebook.testWithClause({{ArgType::ATTRREF, "s.stmt#"}, {ArgType::ATTRREF, "c.stmt#"}}));
        REQUIRE_NOTHROW(rulebook.testWithClause({{ArgType::ATTRREF, "s.stmt#"}, {ArgType::ATTRREF, "cst.value"}}));
        REQUIRE_NOTHROW(rulebook.testWithClause({{ArgType::ATTRREF, "s.stmt#"}, {ArgType::CONSTANT, "1"}}));
        REQUIRE_NOTHROW(rulebook.testWithClause({{ArgType::ATTRREF, "v.varName"}, {ArgType::EXPRESSION, "1"}}));
        REQUIRE_NOTHROW(rulebook.testWithClause({{ArgType::ATTRREF, "v.varName"}, {ArgType::ATTRREF, "c.procName"}}));

        REQUIRE_THROWS(rulebook.testWithClause({{ArgType::EXPRESSION, "1"}, {ArgType::CONSTANT, "1"}}));
        REQUIRE_THROWS(rulebook.testWithClause({{ArgType::EXPRESSION, "1"}, {ArgType::ATTRREF, "s.stmt#"}}));
        REQUIRE_THROWS(rulebook.testWithClause({{ArgType::ATTRREF, "s.stmt#"}, {ArgType::ATTRREF, "c.procName"}}));
    }
}