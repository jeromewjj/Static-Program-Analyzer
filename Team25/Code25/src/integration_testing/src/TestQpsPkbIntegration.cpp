#include "PKB/Interfaces/PKBWriter.h"
#include "PKB/PKB.h"
#include "catch.hpp"
#include "general/SPA.h"

/**
 *
 *
    procedure A {
    1.  read x;
    2.  read y;
    3.  print y;
    4.  while (x > y) {
    5.      if (x > 0) then {
    6.          y = y + y;
            } else {
    7.          x = x - 1;
            }
    8.      while (x == 1) {
    9.          y = 5 + y;
    10.         x = x + y - 10;
            }
        }
    }

    procedure B {
    11. call A;
    }
 *
 *
 */
PKB buildPkbProgram1() {
    PKB pkb;
    auto pkbWriter = PKBWriter(pkb);

    // Add procedure
    unordered_set<Procedure> procSet = {"A", "B"};
    pkbWriter.setProcedures(procSet);

    // Add constant
    unordered_set<Constant> constSet = {"0", "1", "5", "10"};
    pkbWriter.setConstants(constSet);

    // Add variable
    unordered_set<Constant> varSet = {"x", "y"};
    pkbWriter.setVariables(varSet);

    // Add statements
    unordered_set<Statement> stmtSet = {{READ, 1},   {READ, 2},  {PRINT, 3},  {WHILE, 4},   {IF, 5},   {ASSIGN, 6},
                                        {ASSIGN, 7}, {WHILE, 8}, {ASSIGN, 9}, {ASSIGN, 10}, {CALL, 11}};
    pkbWriter.setStatements(stmtSet);

    // Add Follows relationship
    unordered_set<RelationshipTypes::FOLLOWS_PAIR> followsSet = {{1, 2}, {2, 3}, {3, 4}, {5, 8}, {9, 10}};
    pkbWriter.setFollowsRelationship(followsSet);

    // Add Parent relationship
    unordered_set<RelationshipTypes::PARENT_PAIR> parentSet = {{4, 5}, {4, 8}, {5, 6}, {5, 7}, {8, 9}, {8, 10}};
    pkbWriter.setParentsRelationship(parentSet);

    // Add Uses Statement relationship
    unordered_set<RelationshipTypes::STATEMENT_USES_PAIR> usesStmtSet = {
        {3, "y"}, {4, "x"}, {4, "y"}, {5, "x"},  {5, "y"},  {6, "y"},  {7, "x"},
        {8, "x"}, {8, "y"}, {9, "y"}, {10, "x"}, {10, "y"}, {11, "x"}, {11, "y"}};
    pkbWriter.setStatementUsesRelationship(usesStmtSet);

    // Add Uses Procedure relationship
    unordered_set<RelationshipTypes::PROCEDURE_USES_PAIR> usesProcSet = {
        {"A", "x"},
        {"A", "y"},
        {"B", "x"},
        {"B", "y"},
    };
    pkbWriter.setProcedureUsesRelationship(usesProcSet);

    // Add Modifies Statement relationship
    unordered_set<RelationshipTypes::STATEMENT_MODIFIES_PAIR> modifiesStmtSet = {
        {1, "x"}, {2, "y"}, {4, "x"}, {4, "y"}, {5, "x"},  {5, "y"},  {6, "y"},
        {7, "x"}, {8, "x"}, {8, "y"}, {9, "y"}, {10, "x"}, {11, "x"}, {11, "y"},
    };
    pkbWriter.setStatementModifiesRelationship(modifiesStmtSet);

    // Add Modifies Procedure relationship
    unordered_set<RelationshipTypes::PROCEDURE_MODIFIES_PAIR> modifiesProcSet = {
        {"A", "x"},
        {"A", "y"},
        {"B", "x"},
        {"B", "y"},
    };
    pkbWriter.setProcedureModifiesRelationship(modifiesProcSet);

    // Add Assign Pattern
    unordered_set<Assign> assignSet = {
        {6, "y", "((y)+(y))", {"(y)", "((y)+(y))"}},
        {7, "x", "((x)-(1))", {"(x)", "(1)", "((x)-(1))"}},
        {9, "y", "((5)+(y))", {"(5)", "(y)", "((5)+(y))"}},
        {10, "x", "(((x)+(y))-(10))", {"(y)", "(x)", "(y)", "(10)", "((x)+(y))", "(((x)+(y))-(10))"}}};
    pkbWriter.setAssignPatterns(assignSet);

    // Add If Pattern
    unordered_set<RelationshipTypes::If_PAIR> ifSet = {
        {5, "x"},
    };
    pkbWriter.setIfStatements(ifSet);

    // Add While Pattern
    unordered_set<RelationshipTypes::WHILE_PAIR> whileSet = {
        {4, "x"},
        {4, "y"},
        {8, "x"},
    };
    pkbWriter.setWhileStatements(whileSet);

    // Add Call Relationship
    unordered_set<RelationshipTypes::CALLS_PAIR> callsSet = {
        {"B", "A"},
    };
    pkbWriter.setCallsRelationships(callsSet);

    CFGStore::CFGBlockSet cfgSet = {
        {1, "A", CFGBlockType::START_PROC, {}, {2}},   {2, "A", CFGBlockType::NORMAL, {1, 2, 3}, {3}},
        {3, "A", CFGBlockType::NORMAL, {4}, {4, 12}},  {4, "A", CFGBlockType::NORMAL, {5}, {5, 6}},
        {5, "A", CFGBlockType::NORMAL, {6}, {7}},      {6, "A", CFGBlockType::NORMAL, {7}, {7}},
        {7, "A", CFGBlockType::DUMMY, {0}, {8}},       {8, "A", CFGBlockType::NORMAL, {8}, {9, 11}},
        {9, "A", CFGBlockType::NORMAL, {9, 10}, {10}}, {10, "A", CFGBlockType::DUMMY, {}, {8}},
        {11, "A", CFGBlockType::DUMMY, {}, {4}},       {12, "A", CFGBlockType::END_PROC, {}, {}},
        {13, "B", CFGBlockType::START_PROC, {}, {14}}, {14, "B", CFGBlockType::DUMMY, {11}, {}},
    };
    pkbWriter.setCfg(cfgSet);

    return pkb;
}

TEST_CASE("QPS-PKB Integration: Based on basic_source.txt") {
    PKB testPkb = buildPkbProgram1();
    SPA testSpa(testPkb);

    SECTION("Fix error") {
        std::string query = R"/(
        assign a; Select a pattern a ( _ , _ "( y + y)"  _))/";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"6"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Partial Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( _ , _"x"_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"7", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Procedure") {
        std::string query = R"(
		procedure pr;
		Select pr)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<Procedure> procSet(result.begin(), result.end());

        std::unordered_set<Procedure> expectedProcSet = {"A", "B"};
        REQUIRE(procSet == expectedProcSet);
    }

    SECTION("QPS-PKB Entity:Statement") {
        std::string query = R"(
		stmt s;
		Select s)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet{};
        const int EXPECTED_NUM_OF_STMTS = 11;
        for (int i = 1; i <= EXPECTED_NUM_OF_STMTS; i++) {
            expectedStmtSet.insert(std::to_string(i));
        }
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Read") {
        std::string query = R"(
		read r;
		Select r)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Print") {
        std::string query = R"(
		print p;
		Select p)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"3"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Assign") {
        std::string query = R"(
		assign a;
		Select a)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"6", "7", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    // Not required in milestone 1
    SECTION("QPS-PKB Entity:Call") {
        std::string query = R"(
		call c;
		Select c)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"11"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:While") {
        std::string query = R"(
		while w;
		Select w)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "8"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:If") {
        std::string query = R"(
		if i;
		Select i)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Variable") {
        std::string query = R"(
		variable v;
		Select v)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> resultSet(result.begin(), result.end());

        std::unordered_set<string> expectedSet = {"x", "y"};
        REQUIRE(resultSet == expectedSet);
    }

    SECTION("QPS-PKB Entity:Constant") {
        std::string query = R"(
		constant c;
		Select c)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> resultSet(result.begin(), result.end());

        std::unordered_set<string> expectedSet = {"0", "1", "5", "10"};
        REQUIRE(resultSet == expectedSet);
    }

    SECTION("QPS-PKB Relation:Follows Get all followee") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Follows(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3", "5", "9"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Follows Get all follower") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Follows(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3", "4", "8", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Follows star Get all followee start") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Follows*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3", "5", "9"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Follows star Get all follower star") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Follows*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3", "4", "8", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent Get all Parent") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Parent(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "5", "8"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent Get all children") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Parent(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5", "6", "7", "8", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent Star Get all Parent star") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Parent*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "5", "8"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent star Get all children star") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Parent*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5", "6", "7", "8", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Uses Statement Get all statement") {
        std::string query = R"(
		stmt s; variable v;
		Select s such that Uses(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"3", "4", "5", "6", "7", "8", "9", "10", "11"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Use Statement Get all variable") {
        std::string query = R"(
		stmt s; variable v;
		Select v such that Uses(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Uses Procedure Get all procedure") {
        std::string query = R"(
		procedure p; variable v;
		Select p such that Uses(p, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A", "B"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Use Procedure Get all variable") {
        std::string query = R"(
		procedure p; variable v;
		Select v such that Uses(p, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Statement Get all statement") {
        std::string query = R"(
		stmt s; variable v;
		Select s such that Modifies(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "4", "5", "6", "7", "8", "9", "10", "11"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Statement Get all variable") {
        std::string query = R"(
		stmt s; variable v;
		Select v such that Modifies(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Procedure Get all procedure") {
        std::string query = R"(
		procedure p; variable v;
		Select p such that Modifies(p, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A", "B"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Procedure Get all variable") {
        std::string query = R"(
		procedure p; variable v;
		Select v such that Modifies(p, v))";
        vector<string> result = testSpa.evaluate(query);

        std::unordered_set<string> stmtSet{result.begin(), result.end()};
        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Exact Pattern") {
        std::string query = R"(
            assign a;
            Select a pattern a ( _ , "x+y-10"))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Partial Pattern") {
        std::string query = R"(
            assign a;
            Select a pattern a ( _ , _"x"_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"7", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB One Such That One Pattern") {
        std::string query = R"(
            assign a;
            Select a pattern a ( _ , _"x"_) such that Modifies(a, "x"))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"7", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB One Such That One Pattern") {
        std::string query = R"(
            assign a;
            Select a pattern a ( _ , _"x"_) such that Modifies(a, "x"))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"7", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:IF Pattern") {
        std::string query = R"(
            if i;
            Select i pattern i (_,_,_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:WHILE Pattern") {
        std::string query = R"(
            while w;
            Select w pattern w (_,_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "8"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    /*
    SECTION("QPS-PKB Relation:Calls Get all caller") {
        std::string query = R"(
        procedure p1, p2;
        Select p1 such that Calls(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"B"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Get all callee") {
        std::string query = R"(
        procedure p1, p2;
        Select p2 such that Calls(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls* Get all caller star") {
        std::string query = R"(
        procedure p1, p2;
        Select p1 such that Calls*(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"B"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls* Get all callee star") {
        std::string query = R"(
        procedure p1, p2;
        Select p2 such that Calls*(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next Get all previous") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Next(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next Get all next") {
        std::string query = R"(
        stmt s1, s2;
        Select s2 such that Next(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3", "4", "5", "6", "7", "8", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next* Get all previous star") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Next*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next* Get all next star") {
        std::string query = R"(
        stmt s1, s2;
        Select s2 such that Next*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3", "4", "5", "6", "7", "8", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Affects Get all affecting stmt") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Affects(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"6", "7", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next* Get all affected") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Affects(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"6", "7", "9", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }
     */
}

/**
 *
 *
 *
    procedure A {
1.      read x;
2.      read y;
3.      print y;
4.      while (x > y) {
5.          if (x > 0) then {
6.              y = y + y;
7.              call B;
            } else {
8.              x = x - 1;
9.              call C;
            }

10.         while (x == 1) {
11.             y = 5 + y;
12.             x = x + y - 10;
            }
        }
    }

    procedure B {
13.     call D;
    }

    procedure C {
14.     y = 5 + y;
15.     x = x + y - 10;
    }

    procedure D {
16.     y = y + y;
17.     call C;
    }
 *
 */
PKB buildPkbProgram2() {
    PKB pkb;
    auto pkbWriter = PKBWriter(pkb);

    // Add procedure
    unordered_set<Procedure> procSet = {"A", "B", "C", "D"};
    pkbWriter.setProcedures(procSet);

    // Add constant
    unordered_set<Constant> constSet = {"0", "1", "5", "10"};
    pkbWriter.setConstants(constSet);

    // Add variable
    unordered_set<Constant> varSet = {"x", "y"};
    pkbWriter.setVariables(varSet);

    // Add statements
    unordered_set<Statement> stmtSet = {{READ, 1},    {READ, 2},    {PRINT, 3},  {WHILE, 4},   {IF, 5},
                                        {ASSIGN, 6},  {CALL, 7},    {ASSIGN, 8}, {CALL, 9},    {WHILE, 10},
                                        {ASSIGN, 11}, {ASSIGN, 12}, {CALL, 13},  {ASSIGN, 14}, {ASSIGN, 15},
                                        {ASSIGN, 16}, {CALL, 17}};
    pkbWriter.setStatements(stmtSet);

    // Add Follows relationship
    unordered_set<RelationshipTypes::FOLLOWS_PAIR> followsSet = {{1, 2}, {2, 3},   {3, 4},   {5, 10}, {6, 7},
                                                                 {8, 9}, {11, 12}, {14, 15}, {16, 17}};
    pkbWriter.setFollowsRelationship(followsSet);

    // Add Parent relationship
    unordered_set<RelationshipTypes::PARENT_PAIR> parentSet = {{4, 5}, {4, 10}, {5, 6},   {5, 7},
                                                               {5, 8}, {5, 9},  {10, 11}, {10, 12}};
    pkbWriter.setParentsRelationship(parentSet);

    // Add Uses Statement relationship
    unordered_set<RelationshipTypes::STATEMENT_USES_PAIR> usesStmtSet = {
        {3, "y"},  {4, "x"},  {4, "y"},  {5, "x"},  {5, "y"},  {6, "y"},  {7, "x"},  {7, "y"},  {8, "x"},
        {8, "y"},  {9, "x"},  {9, "y"},  {10, "x"}, {10, "y"}, {11, "y"}, {12, "x"}, {12, "y"}, {13, "x"},
        {13, "y"}, {14, "y"}, {15, "x"}, {15, "x"}, {16, "y"}, {17, "x"}, {17, "y"}};
    pkbWriter.setStatementUsesRelationship(usesStmtSet);

    // Add Uses Procedure relationship
    unordered_set<RelationshipTypes::PROCEDURE_USES_PAIR> usesProcSet = {
        {"A", "x"}, {"A", "y"}, {"B", "x"}, {"B", "y"}, {"C", "x"}, {"C", "y"}, {"D", "x"}, {"D", "y"},
    };
    pkbWriter.setProcedureUsesRelationship(usesProcSet);

    // Add Modifies Statement relationship
    unordered_set<RelationshipTypes::STATEMENT_MODIFIES_PAIR> modifiesStmtSet = {
        {1, "x"},  {2, "y"},  {4, "x"},  {4, "y"},  {5, "x"},  {5, "y"},  {6, "y"},  {7, "x"},
        {7, "y"},  {8, "x"},  {8, "y"},  {9, "x"},  {9, "y"},  {10, "x"}, {10, "y"}, {11, "y"},
        {12, "x"}, {13, "x"}, {13, "y"}, {14, "y"}, {15, "x"}, {16, "y"}, {17, "x"}, {17, "y"}};
    pkbWriter.setStatementModifiesRelationship(modifiesStmtSet);

    // Add Modifies Procedure relationship
    unordered_set<RelationshipTypes::PROCEDURE_MODIFIES_PAIR> modifiesProcSet = {
        {"A", "x"}, {"A", "y"}, {"B", "x"}, {"B", "y"}, {"C", "x"}, {"C", "y"}, {"D", "x"}, {"D", "y"},
    };
    pkbWriter.setProcedureModifiesRelationship(modifiesProcSet);

    // Add Assign Pattern
    unordered_set<Assign> assignSet = {
        {6, "y", "((y)+(y))", {"(y)", "((y)+(y))"}},
        {8, "x", "((x)-(1))", {"(x)", "(1)", "((x)-(1))"}},
        {11, "y", "((5)+(y))", {"(5)", "(y)", "((5)+(y))"}},
        {12, "x", "(((x)+(y))-(10))", {"(y)", "(x)", "(y)", "(10)", "((x)+(y))", "(((x)+(y))-(10))"}},
        {14, "y", "((5)+(y))", {"(5)", "(y)", "((5)+(y))"}},
        {15, "x", "(((x)+(y))-(10))", {"(y)", "(x)", "(y)", "(10)", "((x)+(y))", "(((x)+(y))-(10))"}},
        {16, "y", "((y)+(y))", {"(y)", "((y)+(y))"}},
    };
    pkbWriter.setAssignPatterns(assignSet);

    // Add If Pattern
    unordered_set<RelationshipTypes::If_PAIR> ifSet = {
        {5, "x"},
    };
    pkbWriter.setIfStatements(ifSet);

    // Add While Pattern
    unordered_set<RelationshipTypes::WHILE_PAIR> whileSet = {
        {4, "x"},
        {4, "y"},
        {10, "x"},
    };
    pkbWriter.setWhileStatements(whileSet);

    // Add Calls relationship
    unordered_set<RelationshipTypes::CALLS_PAIR> callsSet = {
        {"A", "B"},
        {"A", "C"},
        {"B", "D"},
        {"D", "C"},
    };
    pkbWriter.setCallsRelationships(callsSet);

    CFGStore::CFGBlockSet cfgSet = {
        {1, "A", CFGBlockType::START_PROC, {}, {2}},    {2, "A", CFGBlockType::NORMAL, {1, 2, 3}, {3}},
        {3, "A", CFGBlockType::NORMAL, {4}, {4, 12}},   {4, "A", CFGBlockType::NORMAL, {5}, {5, 6}},
        {5, "A", CFGBlockType::NORMAL, {6, 7}, {7}},    {6, "A", CFGBlockType::NORMAL, {8, 9}, {7}},
        {7, "A", CFGBlockType::DUMMY, {0}, {8}},        {8, "A", CFGBlockType::NORMAL, {10}, {9, 11}},
        {9, "A", CFGBlockType::NORMAL, {11, 12}, {10}}, {10, "A", CFGBlockType::DUMMY, {}, {8}},
        {11, "A", CFGBlockType::DUMMY, {}, {4}},        {12, "A", CFGBlockType::END_PROC, {}, {}},
        {13, "B", CFGBlockType::START_PROC, {}, {14}},  {14, "B", CFGBlockType::DUMMY, {13}, {}},
        {15, "C", CFGBlockType::START_PROC, {}, {16}},  {16, "C", CFGBlockType::DUMMY, {14, 15}, {}},
        {17, "D", CFGBlockType::START_PROC, {}, {18}},  {18, "D", CFGBlockType::DUMMY, {16, 17}, {}},
    };
    pkbWriter.setCfg(cfgSet);

    return pkb;
}

TEST_CASE("QPS-PKB Integration: Based on multi_procedures_source.txt") {
    PKB testPkb = buildPkbProgram2();
    SPA testSpa(testPkb);

    SECTION("QPS-PKB Entity:Procedure") {
        std::string query = R"(
		procedure pr;
		Select pr)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<Procedure> procSet(result.begin(), result.end());
        std::unordered_set<Procedure> expectedProcSet = {"A", "B", "C", "D"};
        REQUIRE(procSet == expectedProcSet);
    }

    SECTION("QPS-PKB Entity:Statement") {
        std::string query = R"(
		stmt s;
		Select s)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1",  "2",  "3",  "4",  "5",  "6",  "7",  "8", "9",
                                                      "10", "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Read") {
        std::string query = R"(
		read r;
		Select r)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Print") {
        std::string query = R"(
		print p;
		Select p)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"3"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Assign") {
        std::string query = R"(
		assign a;
		Select a)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"6", "8", "11", "12", "14", "15", "16"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Call") {
        std::string query = R"(
		call c;
		Select c)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"7", "9", "13", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:While") {
        std::string query = R"(
		while w;
		Select w)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:If") {
        std::string query = R"(
		if i;
		Select i)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Entity:Variable") {
        std::string query = R"(
		variable v;
		Select v)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> resultSet(result.begin(), result.end());

        std::unordered_set<string> expectedSet = {"x", "y"};
        REQUIRE(resultSet == expectedSet);
    }

    SECTION("QPS-PKB Entity:Constant") {
        std::string query = R"(
		constant c;
		Select c)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> resultSet(result.begin(), result.end());

        std::unordered_set<string> expectedSet = {"0", "1", "5", "10"};
        REQUIRE(resultSet == expectedSet);
    }

    SECTION("QPS-PKB Relation:Follows Get all followee") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Follows(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3", "5", "6", "8", "11", "14", "16"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Follows Get all follower") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Follows(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3", "4", "7", "9", "10", "12", "15", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Follows star Get all followee start") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Follows*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3", "5", "6", "8", "11", "14", "16"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Follows star Get all follower star") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Follows*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3", "4", "7", "9", "10", "12", "15", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent Get all Parent") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Parent(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "5", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent Get all Parent with with clause") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Parent(s1, s2) with s1.stmt# = 5)";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent Get all children") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Parent(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5", "6", "7", "8", "9", "10", "11", "12"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent Star Get all Parent star") {
        std::string query = R"(
		stmt s1, s2;
		Select s1 such that Parent*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "5", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Parent star Get all children star") {
        std::string query = R"(
		stmt s1, s2;
		Select s2 such that Parent*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5", "6", "7", "8", "9", "10", "11", "12"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Uses Statement Get all statement") {
        std::string query = R"(
		stmt s; variable v;
		Select s such that Uses(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"3",  "4",  "5",  "6",  "7",  "8",  "9", "10",
                                                      "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Use Statement Get all variable") {
        std::string query = R"(
		stmt s; variable v;
		Select v such that Uses(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Uses Procedure Get all procedure") {
        std::string query = R"(
		procedure p; variable v;
		Select p such that Uses(p, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A", "B", "C", "D"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Use Procedure Get all variable") {
        std::string query = R"(
		procedure p; variable v;
		Select v such that Uses(p, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Statement Get all statement") {
        std::string query = R"(
		stmt s; variable v;
		Select s such that Modifies(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1",  "2",  "4",  "5",  "6",  "7",  "8",  "9",
                                                      "10", "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Statement Get all variable") {
        std::string query = R"(
		stmt s; variable v;
		Select v such that Modifies(s, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Procedure Get all procedure") {
        std::string query = R"(
		procedure p; variable v;
		Select p such that Modifies(p, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A", "B", "C", "D"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Modifies Procedure Get all variable") {
        std::string query = R"(
		procedure p; variable v;
		Select v such that Modifies(p, v))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"x", "y"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Exact Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( _ , "x+y-10"))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"12", "15"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Partial Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( _ , _"x"_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"8", "12", "15"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Exact variable and expression Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( "x" , "x+y-10"))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"12", "15"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Exact variable and Partial expression  Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( "x" , _"x"_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"8", "12", "15"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign Exact variable and wildcard expression  Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( "x" , _ ))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"8", "12", "15"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:Assign wildcard variable and wildcard expression Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( _ , _))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"6", "8", "11", "12", "14", "15", "16"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB One Such That One Pattern") {
        std::string query = R"(
		assign a;
		Select a pattern a ( _ , _"x"_) such that Modifies(a, "x"))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"8", "12", "15"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Relation Get all caller") {
        std::string query = R"(
		procedure p1, p2;
		Select p1 such that Calls(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A", "B", "D"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Relation Get all callee") {
        std::string query = R"(
		procedure p1, p2;
		Select p2 such that Calls(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"B", "C", "D"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Relation Get all callee") {
        std::string query = R"(
		procedure p1, p2;
		Select p2 such that not Calls(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"D", "C", "B", "A"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Relation Get all caller star") {
        std::string query = R"(
		procedure p1, p2;
		Select p1 such that Calls*(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"A", "B", "D"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Relation Get all callee star") {
        std::string query = R"(
		procedure p1, p2;
		Select p2 such that Calls*(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"B", "C", "D"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Relation Get all callee star (Boolean result)") {
        std::string query = R"(
		procedure p1, p2;
		Select BOOLEAN such that Calls*(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"TRUE"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Calls Relation Get all callee star (Tuple result)") {
        std::string query = R"(
		procedure p1, p2;
		Select < p1, p2 > such that Calls*(p1, p2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"D C", "B D", "B C", "A D", "A C", "A B"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:IF Pattern") {
        std::string query = R"(
            if i;
            Select i pattern i (_,_,_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"5"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Pattern:WHILE Pattern") {
        std::string query = R"(
            while w;
            Select w pattern w (_,_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"4", "10"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    /*
    SECTION("QPS-PKB Relation:Next Get all previous") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Next(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3",  "4",  "5",  "6",  "7",
                                                      "8", "9", "10", "11", "12", "14", "16"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next Get all next") {
        std::string query = R"(
        stmt s1, s2;
        Select s2 such that Next(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3",  "4",  "5",  "6",  "7", "8",
                                                      "9", "10", "11", "12", "15", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next* Get all previous star") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Next*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"1", "2", "3",  "4",  "5",  "6",  "7",
                                                      "8", "9", "10", "11", "12", "14", "16"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next* Get all next star") {
        std::string query = R"(
        stmt s1, s2;
        Select s2 such that Next*(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"2", "3",  "4",  "5",  "6",  "7", "8",
                                                      "9", "10", "11", "12", "15", "17"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Affects Get all affecting stmt") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Affects(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"11", "12", "14"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next* Get all affected") {
        std::string query = R"(
        stmt s1, s2;
        Select s1 such that Affects(s1, s2))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"11", "12", "14"};
        REQUIRE(stmtSet == expectedStmtSet);
    }
     */
}