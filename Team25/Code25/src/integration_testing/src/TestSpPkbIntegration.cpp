#include <filesystem>

#include "PKB/Interfaces/PKBReader.h"
#include "PKB/PKB.h"
#include "catch.hpp"
#include "general/SPA.h"

TEST_CASE("SP-PKB Integration: Valid Source Program 1 (basic_source)") {
    PKB testPkb;
    PKBReader testPkbReader(testPkb);
    SPA testSpa(testPkb);

    auto testDirectory = std::filesystem::path(INTEGRATION_TESTING_DIR);
    auto filePath = testDirectory.string() + "basic_source.txt";

    testSpa.parse(filePath);

    SECTION("SP-PKB Entity:Procedure") {
        std::unordered_set<Procedure> procSet = testPkbReader.getProcedures();
        std::unordered_set<Procedure> expectedProcSet = {"A", "B"};
        REQUIRE(procSet == expectedProcSet);
    }

    SECTION("SP-PKB Entity:Statement") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getAllStmtNum();
        std::unordered_set<StmtNum> expectedStmtSet{};
        const int EXPECTED_NUM_OF_STMTS = 11;
        for (int i = 1; i <= EXPECTED_NUM_OF_STMTS; i++) {
            expectedStmtSet.insert(i);
        }
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Read") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(READ);
        std::unordered_set<StmtNum> expectedStmtSet = {1, 2};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Print") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(PRINT);
        std::unordered_set<StmtNum> expectedStmtSet = {3};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Assign") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(ASSIGN);
        std::unordered_set<StmtNum> expectedStmtSet = {6, 7, 9, 10};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    // Not require in milestone 1
    SECTION("SP-PKB Entity:Call") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(CALL);
        std::unordered_set<StmtNum> expectedStmtSet = {11};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:While") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(WHILE);
        std::unordered_set<StmtNum> expectedStmtSet = {4, 8};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:If") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(IF);
        std::unordered_set<StmtNum> expectedStmtSet = {5};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Variable") {
        std::unordered_set<Variable> varSet = testPkbReader.getVariables();
        std::unordered_set<Variable> expectedSet = {"x", "y"};
        REQUIRE(varSet == expectedSet);
    }

    SECTION("SP-PKB Entity:Constant") {
        std::unordered_set<Constant> constSet = testPkbReader.getConstants();
        std::unordered_set<Constant> expectedSet = {"0", "1", "5", "10"};
        REQUIRE(constSet == expectedSet);
    }

    SECTION("SP-PKB Relation:Follows") {
        REQUIRE(testPkbReader.containFollowsRelation(1, 2));
        REQUIRE(testPkbReader.containFollowsRelation(2, 3));
        REQUIRE(testPkbReader.containFollowsRelation(3, 4));
        REQUIRE(testPkbReader.containFollowsRelation(5, 8));
        REQUIRE(testPkbReader.containFollowsRelation(9, 10));
    }

    SECTION("SP-PKB Relation:Follows*") {
        REQUIRE(testPkbReader.containFollowsStarRelation(1, 2));
        REQUIRE(testPkbReader.containFollowsStarRelation(1, 3));
        REQUIRE(testPkbReader.containFollowsStarRelation(1, 4));
        REQUIRE(testPkbReader.containFollowsStarRelation(2, 3));
        REQUIRE(testPkbReader.containFollowsStarRelation(2, 4));
        REQUIRE(testPkbReader.containFollowsStarRelation(3, 4));
        REQUIRE(testPkbReader.containFollowsStarRelation(5, 8));
        REQUIRE(testPkbReader.containFollowsStarRelation(9, 10));
    }

    SECTION("SP-PKB Relation:Parent") {
        REQUIRE(testPkbReader.containParentRelation(4, 5));
        REQUIRE(testPkbReader.containParentRelation(4, 8));
        REQUIRE(testPkbReader.containParentRelation(5, 6));
        REQUIRE(testPkbReader.containParentRelation(5, 7));
        REQUIRE(testPkbReader.containParentRelation(8, 9));
        REQUIRE(testPkbReader.containParentRelation(8, 10));
    }

    SECTION("SP-PKB Relation:Parent*") {
        REQUIRE(testPkbReader.containParentStarRelation(4, 5));
        REQUIRE(testPkbReader.containParentStarRelation(4, 6));
        REQUIRE(testPkbReader.containParentStarRelation(4, 7));
        REQUIRE(testPkbReader.containParentStarRelation(4, 8));
        REQUIRE(testPkbReader.containParentStarRelation(4, 9));
        REQUIRE(testPkbReader.containParentStarRelation(4, 10));
        REQUIRE(testPkbReader.containParentStarRelation(5, 6));
        REQUIRE(testPkbReader.containParentStarRelation(5, 7));
        REQUIRE(testPkbReader.containParentStarRelation(8, 9));
        REQUIRE(testPkbReader.containParentStarRelation(8, 10));
    }

    SECTION("SP-PKB Relation:Uses Statement") {
        REQUIRE(testPkbReader.containStmtUsesRelation(3, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(4, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(4, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(5, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(5, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(6, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(7, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(8, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(8, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(9, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(10, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(10, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(11, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(11, "y"));
    }

    SECTION("SP-PKB Relation:Uses Procedure") {
        REQUIRE(testPkbReader.containProcUsesRelation("A", "x"));
        REQUIRE(testPkbReader.containProcUsesRelation("A", "y"));
        REQUIRE(testPkbReader.containProcUsesRelation("B", "x"));
        REQUIRE(testPkbReader.containProcUsesRelation("B", "y"));
    }

    SECTION("SP-PKB Relation:Modifies Statement") {
        REQUIRE(testPkbReader.containStmtModifiesRelation(1, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(2, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(4, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(4, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(5, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(5, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(6, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(7, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(8, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(8, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(9, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(10, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(11, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(11, "y"));
    }

    SECTION("SP-PKB Relation:Modifies Procedure") {
        REQUIRE(testPkbReader.containProcModifiesRelation("A", "x"));
        REQUIRE(testPkbReader.containProcModifiesRelation("A", "y"));
        REQUIRE(testPkbReader.containProcModifiesRelation("B", "x"));
        REQUIRE(testPkbReader.containProcModifiesRelation("B", "y"));
    }

    SECTION("SP-PKB Pattern:Assign Exact Expression") {
        REQUIRE(testPkbReader.containAssignPattern(6, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((y)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(7, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "((x)-(1))"}));
        REQUIRE(testPkbReader.containAssignPattern(9, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((5)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(10, {ArgType::SYNONYM, "x"},
                                                   {ArgType::WILDCARD_EXPR, "(((x)+(y))-(10))"}));
    }

    SECTION("SP-PKB Pattern:Assign Partial Expression") {
        REQUIRE(testPkbReader.containAssignPattern(6, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((y)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(6, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(testPkbReader.containAssignPattern(7, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "((x)-(1))"}));
        REQUIRE(testPkbReader.containAssignPattern(7, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(x)"}));
        REQUIRE(testPkbReader.containAssignPattern(7, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(1)"}));
        REQUIRE(testPkbReader.containAssignPattern(9, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((5)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(9, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(5)"}));
        REQUIRE(testPkbReader.containAssignPattern(9, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(testPkbReader.containAssignPattern(10, {ArgType::SYNONYM, "x"},
                                                   {ArgType::WILDCARD_EXPR, "(((x)+(y))-(10))"}));
        REQUIRE(testPkbReader.containAssignPattern(10, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "((x)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(10, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(10)"}));
        REQUIRE(testPkbReader.containAssignPattern(10, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(x)"}));
        REQUIRE(testPkbReader.containAssignPattern(10, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(y)"}));
    }

    SECTION("SP-PKB Pattern:IF Expression") {
        REQUIRE(testPkbReader.containIfPattern(5, {ArgType::SYNONYM, "x"}));
    }

    SECTION("SP-PKB Pattern:WHILE Expression") {
        REQUIRE(testPkbReader.containWhilePattern(4, {ArgType::SYNONYM, "x"}));
        REQUIRE(testPkbReader.containWhilePattern(4, {ArgType::SYNONYM, "y"}));
        REQUIRE(testPkbReader.containWhilePattern(8, {ArgType::SYNONYM, "x"}));
    }

    SECTION("SP-PKB Relation:Calls") {
        REQUIRE(testPkbReader.containCallsRelation({ArgType::SYNONYM, "B"}, {ArgType::SYNONYM, "A"}));
    }

    SECTION("SP-PKB Relation:Calls*") {
        REQUIRE(testPkbReader.containCallsRelation({ArgType::SYNONYM, "B"}, {ArgType::SYNONYM, "A"}));
    }

    SECTION("SP-PKB Relation:Next") {
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "1"}, {ArgType::SYNONYM, "2"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "2"}, {ArgType::SYNONYM, "3"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "3"}, {ArgType::SYNONYM, "4"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "4"}, {ArgType::SYNONYM, "5"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "5"}, {ArgType::SYNONYM, "6"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "5"}, {ArgType::SYNONYM, "7"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "6"}, {ArgType::SYNONYM, "8"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "7"}, {ArgType::SYNONYM, "8"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "8"}, {ArgType::SYNONYM, "4"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "8"}, {ArgType::SYNONYM, "9"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "9"}, {ArgType::SYNONYM, "10"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "10"}, {ArgType::SYNONYM, "8"}));
    }

    SECTION("SP-PKB Relation:Affects") {
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "6"}, {ArgType::SYNONYM, "6"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "6"}, {ArgType::SYNONYM, "9"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "7"}, {ArgType::SYNONYM, "7"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "7"}, {ArgType::SYNONYM, "10"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "9"}, {ArgType::SYNONYM, "6"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "9"}, {ArgType::SYNONYM, "9"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "9"}, {ArgType::SYNONYM, "10"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "10"}, {ArgType::SYNONYM, "7"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "10"}, {ArgType::SYNONYM, "10"}));
    }
}

TEST_CASE("SP-PKB Integration: Valid Source Program 2 (multi_procedures_source)") {
    PKB testPkb;
    PKBReader testPkbReader(testPkb);
    SPA testSpa(testPkb);

    auto testDirectory = std::filesystem::path(INTEGRATION_TESTING_DIR);
    auto filePath = testDirectory.string() + "multi_procedures_source.txt";

    testSpa.parse(filePath);

    SECTION("SP-PKB Entity:Procedure") {
        std::unordered_set<Procedure> procSet = testPkbReader.getProcedures();
        std::unordered_set<Procedure> expectedProcSet = {"A", "B", "C", "D"};
        REQUIRE(procSet == expectedProcSet);
    }

    SECTION("SP-PKB Entity:Statement") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getAllStmtNum();
        std::unordered_set<StmtNum> expectedStmtSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Read") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(READ);
        std::unordered_set<StmtNum> expectedStmtSet = {1, 2};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Print") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(PRINT);
        std::unordered_set<StmtNum> expectedStmtSet = {3};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Assign") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(ASSIGN);
        std::unordered_set<StmtNum> expectedStmtSet = {6, 8, 11, 12, 14, 15, 16};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Call") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(CALL);
        std::unordered_set<StmtNum> expectedStmtSet = {7, 9, 13, 17};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:While") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(WHILE);
        std::unordered_set<StmtNum> expectedStmtSet = {4, 10};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:If") {
        std::unordered_set<StmtNum> stmtSet = testPkbReader.getStmtNum(IF);
        std::unordered_set<StmtNum> expectedStmtSet = {5};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("SP-PKB Entity:Variable") {
        std::unordered_set<Variable> varSet = testPkbReader.getVariables();
        std::unordered_set<Variable> expectedSet = {"x", "y"};
        REQUIRE(varSet == expectedSet);
    }

    SECTION("SP-PKB Entity:Constant") {
        std::unordered_set<Constant> constSet = testPkbReader.getConstants();
        std::unordered_set<Constant> expectedSet = {"0", "1", "5", "10"};
        REQUIRE(constSet == expectedSet);
    }

    SECTION("SP-PKB Relation:Follows") {
        REQUIRE(testPkbReader.containFollowsRelation(1, 2));
        REQUIRE(testPkbReader.containFollowsRelation(2, 3));
        REQUIRE(testPkbReader.containFollowsRelation(3, 4));
        REQUIRE(testPkbReader.containFollowsRelation(5, 10));
        REQUIRE(testPkbReader.containFollowsRelation(6, 7));
        REQUIRE(testPkbReader.containFollowsRelation(8, 9));
        REQUIRE(testPkbReader.containFollowsRelation(11, 12));
        REQUIRE(testPkbReader.containFollowsRelation(14, 15));
        REQUIRE(testPkbReader.containFollowsRelation(16, 17));
    }

    SECTION("SP-PKB Relation:Follows*") {
        REQUIRE(testPkbReader.containFollowsStarRelation(1, 2));
        REQUIRE(testPkbReader.containFollowsStarRelation(1, 3));
        REQUIRE(testPkbReader.containFollowsStarRelation(1, 4));
        REQUIRE(testPkbReader.containFollowsStarRelation(2, 3));
        REQUIRE(testPkbReader.containFollowsStarRelation(2, 4));
        REQUIRE(testPkbReader.containFollowsStarRelation(3, 4));
        REQUIRE(testPkbReader.containFollowsStarRelation(5, 10));
        REQUIRE(testPkbReader.containFollowsStarRelation(6, 7));
        REQUIRE(testPkbReader.containFollowsStarRelation(8, 9));
        REQUIRE(testPkbReader.containFollowsStarRelation(11, 12));
        REQUIRE(testPkbReader.containFollowsStarRelation(14, 15));
        REQUIRE(testPkbReader.containFollowsStarRelation(16, 17));
    }

    SECTION("SP-PKB Relation:Parent") {
        REQUIRE(testPkbReader.containParentRelation(4, 5));
        REQUIRE(testPkbReader.containParentRelation(4, 10));
        REQUIRE(testPkbReader.containParentRelation(5, 6));
        REQUIRE(testPkbReader.containParentRelation(5, 7));
        REQUIRE(testPkbReader.containParentRelation(5, 8));
        REQUIRE(testPkbReader.containParentRelation(5, 9));
        REQUIRE(testPkbReader.containParentRelation(10, 11));
        REQUIRE(testPkbReader.containParentRelation(10, 12));
    }

    SECTION("SP-PKB Relation:Parent*") {
        REQUIRE(testPkbReader.containParentStarRelation(4, 5));
        REQUIRE(testPkbReader.containParentStarRelation(4, 6));
        REQUIRE(testPkbReader.containParentStarRelation(4, 7));
        REQUIRE(testPkbReader.containParentStarRelation(4, 8));
        REQUIRE(testPkbReader.containParentStarRelation(4, 9));
        REQUIRE(testPkbReader.containParentStarRelation(4, 10));
        REQUIRE(testPkbReader.containParentStarRelation(4, 11));
        REQUIRE(testPkbReader.containParentStarRelation(4, 12));
        REQUIRE(testPkbReader.containParentStarRelation(5, 6));
        REQUIRE(testPkbReader.containParentStarRelation(5, 7));
        REQUIRE(testPkbReader.containParentStarRelation(5, 8));
        REQUIRE(testPkbReader.containParentStarRelation(5, 9));
        REQUIRE(testPkbReader.containParentStarRelation(10, 11));
        REQUIRE(testPkbReader.containParentStarRelation(10, 12));
    }

    SECTION("SP-PKB Relation:Uses Statement") {
        REQUIRE(testPkbReader.containStmtUsesRelation(3, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(4, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(4, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(5, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(5, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(6, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(7, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(7, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(8, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(9, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(9, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(10, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(10, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(11, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(12, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(12, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(13, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(13, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(14, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(15, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(15, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(16, "y"));
        REQUIRE(testPkbReader.containStmtUsesRelation(17, "x"));
        REQUIRE(testPkbReader.containStmtUsesRelation(17, "y"));
    }

    SECTION("SP-PKB Relation:Uses Procedure") {
        REQUIRE(testPkbReader.containProcUsesRelation("A", "x"));
        REQUIRE(testPkbReader.containProcUsesRelation("A", "y"));
        REQUIRE(testPkbReader.containProcUsesRelation("B", "x"));
        REQUIRE(testPkbReader.containProcUsesRelation("B", "y"));
        REQUIRE(testPkbReader.containProcUsesRelation("C", "x"));
        REQUIRE(testPkbReader.containProcUsesRelation("C", "y"));
        REQUIRE(testPkbReader.containProcUsesRelation("D", "x"));
        REQUIRE(testPkbReader.containProcUsesRelation("D", "y"));
    }

    SECTION("SP-PKB Relation:Modifies Statement") {
        REQUIRE(testPkbReader.containStmtModifiesRelation(1, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(2, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(4, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(4, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(5, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(5, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(6, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(7, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(7, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(8, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(9, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(9, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(10, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(10, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(11, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(12, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(13, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(13, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(14, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(15, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(16, "y"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(17, "x"));
        REQUIRE(testPkbReader.containStmtModifiesRelation(17, "y"));
    }

    SECTION("SP-PKB Relation:Modifies Procedure") {
        REQUIRE(testPkbReader.containProcModifiesRelation("A", "x"));
        REQUIRE(testPkbReader.containProcModifiesRelation("A", "y"));
        REQUIRE(testPkbReader.containProcModifiesRelation("B", "x"));
        REQUIRE(testPkbReader.containProcModifiesRelation("B", "y"));
        REQUIRE(testPkbReader.containProcModifiesRelation("C", "x"));
        REQUIRE(testPkbReader.containProcModifiesRelation("C", "y"));
        REQUIRE(testPkbReader.containProcModifiesRelation("D", "x"));
        REQUIRE(testPkbReader.containProcModifiesRelation("D", "y"));
    }

    SECTION("SP-PKB Pattern:Assign Exact Expression") {
        REQUIRE(testPkbReader.containAssignPattern(6, {ArgType::SYNONYM, "y"}, {ArgType::EXPRESSION, "((y)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(8, {ArgType::SYNONYM, "x"}, {ArgType::EXPRESSION, "((x)-(1))"}));
        REQUIRE(testPkbReader.containAssignPattern(11, {ArgType::SYNONYM, "y"}, {ArgType::EXPRESSION, "((5)+(y))"}));
        REQUIRE(
            testPkbReader.containAssignPattern(12, {ArgType::SYNONYM, "x"}, {ArgType::EXPRESSION, "(((x)+(y))-(10))"}));
        REQUIRE(testPkbReader.containAssignPattern(14, {ArgType::SYNONYM, "y"}, {ArgType::EXPRESSION, "((5)+(y))"}));
        REQUIRE(
            testPkbReader.containAssignPattern(15, {ArgType::SYNONYM, "x"}, {ArgType::EXPRESSION, "(((x)+(y))-(10))"}));
        REQUIRE(testPkbReader.containAssignPattern(16, {ArgType::SYNONYM, "y"}, {ArgType::EXPRESSION, "((y)+(y))"}));
    }

    SECTION("SP-PKB Pattern:Assign Partial Expression") {
        REQUIRE(testPkbReader.containAssignPattern(6, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((y)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(6, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(testPkbReader.containAssignPattern(8, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "((x)-(1))"}));
        REQUIRE(testPkbReader.containAssignPattern(8, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(x)"}));
        REQUIRE(testPkbReader.containAssignPattern(8, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(1)"}));
        REQUIRE(testPkbReader.containAssignPattern(11, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((5)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(11, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(5)"}));
        REQUIRE(testPkbReader.containAssignPattern(11, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(testPkbReader.containAssignPattern(12, {ArgType::SYNONYM, "x"},
                                                   {ArgType::WILDCARD_EXPR, "(((x)+(y))-(10))"}));
        REQUIRE(testPkbReader.containAssignPattern(12, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "((x)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(12, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(10)"}));
        REQUIRE(testPkbReader.containAssignPattern(12, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(x)"}));
        REQUIRE(testPkbReader.containAssignPattern(12, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(testPkbReader.containAssignPattern(14, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((5)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(14, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(5)"}));
        REQUIRE(testPkbReader.containAssignPattern(14, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(testPkbReader.containAssignPattern(15, {ArgType::SYNONYM, "x"},
                                                   {ArgType::WILDCARD_EXPR, "(((x)+(y))-(10))"}));
        REQUIRE(testPkbReader.containAssignPattern(15, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "((x)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(15, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(10)"}));
        REQUIRE(testPkbReader.containAssignPattern(15, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(x)"}));
        REQUIRE(testPkbReader.containAssignPattern(15, {ArgType::SYNONYM, "x"}, {ArgType::WILDCARD_EXPR, "(y)"}));
        REQUIRE(testPkbReader.containAssignPattern(16, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "((y)+(y))"}));
        REQUIRE(testPkbReader.containAssignPattern(16, {ArgType::SYNONYM, "y"}, {ArgType::WILDCARD_EXPR, "(y)"}));
    }

    SECTION("SP-PKB Pattern:IF Expression") {
        REQUIRE(testPkbReader.containIfPattern(5, {ArgType::SYNONYM, "x"}));
    }

    SECTION("SP-PKB Pattern:WHILE Expression") {
        REQUIRE(testPkbReader.containWhilePattern(4, {ArgType::SYNONYM, "x"}));
        REQUIRE(testPkbReader.containWhilePattern(4, {ArgType::SYNONYM, "y"}));
        REQUIRE(testPkbReader.containWhilePattern(10, {ArgType::SYNONYM, "x"}));
    }

    SECTION("SP-PKB Relation:Call") {
        REQUIRE(testPkbReader.containCallsRelation("A", "B"));
        REQUIRE(testPkbReader.containCallsRelation("A", "C"));
        REQUIRE(testPkbReader.containCallsRelation("B", "D"));
        REQUIRE(testPkbReader.containCallsRelation("D", "C"));
    }

    SECTION("SP-PKB Relation:Call*") {
        REQUIRE(testPkbReader.containCallsStarRelation("A", "B"));
        REQUIRE(testPkbReader.containCallsStarRelation("A", "C"));
        REQUIRE(testPkbReader.containCallsStarRelation("A", "D"));
        REQUIRE(testPkbReader.containCallsStarRelation("B", "C"));
        REQUIRE(testPkbReader.containCallsStarRelation("B", "D"));
        REQUIRE(testPkbReader.containCallsStarRelation("D", "C"));
    }

    SECTION("SP-PKB Relation:Next") {
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "1"}, {ArgType::SYNONYM, "2"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "2"}, {ArgType::SYNONYM, "3"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "3"}, {ArgType::SYNONYM, "4"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "4"}, {ArgType::SYNONYM, "5"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "5"}, {ArgType::SYNONYM, "6"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "5"}, {ArgType::SYNONYM, "8"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "6"}, {ArgType::SYNONYM, "7"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "7"}, {ArgType::SYNONYM, "10"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "8"}, {ArgType::SYNONYM, "9"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "9"}, {ArgType::SYNONYM, "10"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "10"}, {ArgType::SYNONYM, "4"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "10"}, {ArgType::SYNONYM, "11"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "11"}, {ArgType::SYNONYM, "12"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "12"}, {ArgType::SYNONYM, "10"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "14"}, {ArgType::SYNONYM, "15"}));
        REQUIRE(testPkbReader.containNextRelation({ArgType::SYNONYM, "16"}, {ArgType::SYNONYM, "17"}));
    }

    SECTION("SP-PKB Relation:Affects") {
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "11"}, {ArgType::SYNONYM, "6"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "11"}, {ArgType::SYNONYM, "11"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "11"}, {ArgType::SYNONYM, "12"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "12"}, {ArgType::SYNONYM, "8"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "12"}, {ArgType::SYNONYM, "12"}));
        REQUIRE(testPkbReader.containAffectRelation({ArgType::SYNONYM, "14"}, {ArgType::SYNONYM, "15"}));
    }
}