#import "../Mocks.h"
#import "QPS/Validator/Rules/Rule.h"
#import "catch.hpp"

TEST_CASE("Test Rules") {
    auto declarations = Mock::Declarations();
    std::unordered_map<std::string, EntityType> map;
    for (const auto& declaration : declarations) {
        map[declaration.synonym] = declaration.entityType;
    }

    SECTION("Test synonymDeclaredOnce") {
        REQUIRE_NOTHROW(Rule::synonymDeclaredOnce(declarations));

        {
            declarations.push_back({EntityType::VARIABLE, "s"});
            REQUIRE_THROWS(Rule::synonymDeclaredOnce(declarations));
            declarations.pop_back();
        }

        REQUIRE_NOTHROW(Rule::synonymDeclaredOnce(declarations));
    }

    SECTION("Test synonymUsedDeclared") {
        REQUIRE_NOTHROW(Rule::synonymUsedDeclared(map, {"s", "s1", "a", "v"}));

        REQUIRE_THROWS(Rule::synonymUsedDeclared(map, {"s", "s1", "a", "vuahaha"}));
    }

    SECTION("Test firstArgNoWildcard") {
        REQUIRE_THROWS(Rule::firstArgNoWildcard({Argument{ArgType::WILDCARD, ""}, Argument{ArgType::SYNONYM, "a"}}));

        REQUIRE_NOTHROW(Rule::firstArgNoWildcard({Argument{ArgType::SYNONYM, "b"}, Argument{ArgType::SYNONYM, "a"}}));
    }

    SECTION("Test abstractionArgSynonymType") {
        Argument arg1{ArgType::SYNONYM, "s"};
        Argument arg2{ArgType::SYNONYM, "a"};
        REQUIRE_NOTHROW(Rule::abstractionArgSynonymType(map, Abstraction{AbstractionType::FOLLOWS, {arg1, arg2}}));

        Argument arg3{ArgType::EXPRESSION, "LOL"};
        REQUIRE_NOTHROW(Rule::abstractionArgSynonymType(map, Abstraction{AbstractionType::FOLLOWS, {arg1, arg3}}));

        Argument arg4{ArgType::SYNONYM, "v"};
        REQUIRE_THROWS(Rule::abstractionArgSynonymType(map, Abstraction{AbstractionType::FOLLOWS, {arg1, arg4}}));
        REQUIRE_THROWS(Rule::abstractionArgSynonymType(map, Abstraction{AbstractionType::FOLLOWS, {arg4, arg2}}));
    }

    SECTION("Test abstractionArgSynonymType") {
        Argument arg1{ArgType::SYNONYM, "v"};
        REQUIRE_NOTHROW(Rule::patternArgSynonymType(map, EntityType::ASSIGN, {arg1}));

        Argument arg2{ArgType::EXPRESSION, "LOL"};
        REQUIRE_NOTHROW(Rule::patternArgSynonymType(map, EntityType::ASSIGN, {arg2}));

        Argument arg3{ArgType::SYNONYM, "a"};
        REQUIRE_THROWS(Rule::patternArgSynonymType(map, EntityType::ASSIGN, {arg3}));
    }

    SECTION("Test validAttrRef") {
        REQUIRE_NOTHROW(Rule::validAttrRef(map, "a.stmt#"));
        REQUIRE(Rule::validAttrRef(map, "a.stmt#") == Attribute::ValType::INT);

        REQUIRE_NOTHROW(Rule::validAttrRef(map, "c.procName"));
        REQUIRE(Rule::validAttrRef(map, "c.procName") == Attribute::ValType::STRING);

        REQUIRE_THROWS(Rule::validAttrRef(map, "s.value"));
    }

    SECTION("Test validAttrRef") {
        REQUIRE_NOTHROW(Rule::validAttrCompare(Attribute::ValType::INT, Attribute::ValType::INT));
        REQUIRE_THROWS(Rule::validAttrCompare(Attribute::ValType::INT, Attribute::ValType::STRING));
    }
}