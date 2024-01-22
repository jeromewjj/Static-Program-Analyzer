#include "./Mocks.h"
#include "QPS/Clause/CondClause.h"
#include "QPS/Clause/SelClause.h"
#include "QPS/Evaluator/Entity/Entity.h"
#include "catch.hpp"

// TEST_CASE("Test clauses decorator composition") {
//     SECTION("Only true clause") {
//         Context c = Context{};
//         TrueClause tc = TrueClause{};
//         REQUIRE(tc.evaluate(c));
//     }
//     SECTION("Test one-level such that clause") {
//         Context c = Context{};
//         TrueClause tc = TrueClause{};
//         STClause stc = STClause{&tc};
//     }
//     SECTION("Test one-level pattern clause") {
//         Context c = Context{};
//         TrueClause tc = TrueClause{};
//         PatClause pc = PatClause{&tc};
//     }
//     SECTION("Multi-level multi-clause") {
//         Context c = Context{};
//         TrueClause tc = TrueClause{};
//         PatClause pc = PatClause{&tc};
//         STClause stc = STClause{&pc};
//     }
//     SECTION("Complex multi-level multi-clause") {
//         Context c = Context{};
//         TrueClause tc = TrueClause{};
//         PatClause pc = PatClause{&tc};
//         PatClause pc1 = PatClause{&pc};
//         STClause stc = STClause{&pc1};
//         STClause stc1 = STClause{&stc};
//     }
// }

TEST_CASE("Test select clause") {
    const auto entityComparator = [](Entity& a, Entity& b) {
        if (a.name < b.name) {
            return true;
        }
        else if (a.number < b.number) {
            return true;
        }
        else {
            return a.entityType < b.entityType;
        }
    };

    const auto compareVectors = [entityComparator](const std::vector<Entity>& v1, const std::vector<Entity>& v2) {
        std::vector<Entity> s1 = v1;
        std::vector<Entity> s2 = v2;

        std::sort(s1.begin(), s1.end(), entityComparator);
        std::sort(s2.begin(), s2.end(), entityComparator);
        if (v1.size() != v2.size()) {
            return false;
        }
        for (size_t i = 0; i < s1.size(); i++) {
            if (!(s1[i] == s2[i])) {
                return false;
            }
        }
        return true;
    };

    auto declarations = Mock::Declarations();
    Mock::MockPKBReaderEntity reader;
    // TODO: Replace with ClauseStrategy unit tests

    //    SECTION("check select clause error") {
    //        SelClause sc = SelClause{"v"};
    //        REQUIRE_NOTHROW(sc.evaluate(reader, declarations));
    //    }
    //
    //    SECTION("select all variables") {
    //        SelClause sc = SelClause{"v"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"v_x", 0, EntityType::VARIABLE};
    //        Entity e2 = {"v_y", 0, EntityType::VARIABLE};
    //        Entity e3 = {"v_z", 0, EntityType::VARIABLE};
    //        std::vector<Entity> expected = {e1, e2, e3};
    //        REQUIRE(res.size() == 3);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all statements") {
    //        SelClause sc = SelClause{"s"};
    //        auto res = sc.evaluate(reader, declarations);
    //        std::vector<Entity> expected;
    //        for (int i = 1; i < 14; i++) {
    //            expected.push_back({"", i, EntityType::STATEMENT});
    //        }
    //        REQUIRE(res.size() == 13);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all assign statements") {
    //        SelClause sc = SelClause{"a"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"", 6, EntityType::ASSIGN};
    //        Entity e2 = {"", 7, EntityType::ASSIGN};
    //        Entity e3 = {"", 8, EntityType::ASSIGN};
    //        std::vector<Entity> expected = {e1, e2, e3};
    //        REQUIRE(res.size() == 3);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all read statements") {
    //        SelClause sc = SelClause{"r"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"", 1, EntityType::READ};
    //        Entity e2 = {"", 2, EntityType::READ};
    //        Entity e3 = {"", 3, EntityType::READ};
    //        std::vector<Entity> expected = {e1, e2, e3};
    //        REQUIRE(res.size() == 3);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all if statements") {
    //        SelClause sc = SelClause{"i"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"", 11, EntityType::IF};
    //        Entity e2 = {"", 12, EntityType::IF};
    //        Entity e3 = {"", 13, EntityType::IF};
    //        std::vector<Entity> expected = {e1, e2, e3};
    //        REQUIRE(res.size() == 3);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all print statements") {
    //        SelClause sc = SelClause{"pr"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"", 5, EntityType::PRINT};
    //        Entity e2 = {"", 4, EntityType::PRINT};
    //        std::vector<Entity> expected = {e1, e2};
    //        REQUIRE(res.size() == 2);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all call statements") {
    //        SelClause sc = SelClause{"c"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"", 9, EntityType::CALL};
    //        std::vector<Entity> expected = {e1};
    //        REQUIRE(res.size() == 1);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all while statements") {
    //        SelClause sc = SelClause{"w"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"", 10, EntityType::WHILE};
    //        std::vector<Entity> expected = {e1};
    //        REQUIRE(res.size() == 1);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all procedures") {
    //        SelClause sc = SelClause{"p"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"p_x", 0, EntityType::PROCEDURE};
    //        Entity e2 = {"p_y", 0, EntityType::PROCEDURE};
    //        Entity e3 = {"p_z", 0, EntityType::PROCEDURE};
    //        std::vector<Entity> expected = {e1, e2, e3};
    //        REQUIRE(res.size() == 3);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select all constants") {
    //        SelClause sc = SelClause{"cst"};
    //        auto res = sc.evaluate(reader, declarations);
    //        Entity e1 = {"c_1", 0, EntityType::CONSTANT};
    //        Entity e2 = {"c_2", 0, EntityType::CONSTANT};
    //        Entity e3 = {"c_3", 0, EntityType::CONSTANT};
    //        std::vector<Entity> expected = {e1, e2, e3};
    //        REQUIRE(res.size() == 3);
    //        REQUIRE(compareVectors(res, expected));
    //    }
    //
    //    SECTION("select synonym that doesn't have declaration") {
    //        REQUIRE_THROWS([reader, declarations](){
    //            SelClause sc = SelClause{"hahahihi"};
    //            auto res = sc.evaluate(reader, declarations);
    //        }());
    //    }
}