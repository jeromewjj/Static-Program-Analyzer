#include "../../AST/MockASTs.h"
#include "SP/DesignExtraction/Relationship/UsesRelationshipExtractor.h"
#include "catch.hpp"

TEST_CASE("Should extract Uses of different types (Single-Procedure)", "[UsesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    UsesRelationshipExtractor extractor{pkbAdapter};

    // Code:
    /*
    // Procedure p {
    //1   read x;
    //2   while (x < 0) {
    //3     read x;}
    //
    //4   read y;
    //5   if (y < 0) {
    //6     print y;
    //    } else {
    //7     print x;
    //    }
    // }
    */
    // Used Vars:
    /*
     * 2: x
     * 5: y, x
     * 6: y
     * 7: x
     *
     * p: x,y
     */
    auto progNode = MockASTs::mock2();
    extractor.extractRelationship(progNode);
    std::unordered_map<int, unordered_set<string>> stmtToVars = extractor.getStmtToVarsMap();
    std::unordered_map<string, unordered_set<string>> procToVars = extractor.getProcToVarsMap();

    // expected
    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {2, {"x"}}, {5, {"y", "x"}}, {6, {"y"}}, {7, {"x"}}};
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"p", {"x", "y"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Uses (Multi-Procedure Calls) - simple", "[UsesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    UsesRelationshipExtractor extractor{pkbAdapter};
    // Code:
    /*
     Procedure p1 {
       x = y;
     }
     Procedure p2 {
       call p1;
     }
     Procedure p3 {
       call p2;
     }
    */
    auto programNode = MockASTs::MultiProcedureCalls::mock0();
    extractor.extractRelationship(programNode);
    std::unordered_map<int, unordered_set<string>> stmtToVars = extractor.getStmtToVarsMap();
    std::unordered_map<string, unordered_set<string>> procToVars = extractor.getProcToVarsMap();

    // expected
    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {1, {"y"}},
        {2, {"y"}},
        {3, {"y"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"p1", {"y"}},
        {"p2", {"y"}},
        {"p3", {"y"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Uses between (Multi-Procedure Calls) - long chain", "[UsesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    UsesRelationshipExtractor extractor{pkbAdapter};
    // Code:
    /*
        Procedure p1 { x = y; }
        Procedure p2 { call p1; }
        Procedure p3 { call p2; }
        Procedure p4 { call p3; }
        Procedure p5 { call p4; }
     */
    auto programNode = MockASTs::MultiProcedureCalls::mock1();
    extractor.extractRelationship(programNode);
    std::unordered_map<int, unordered_set<string>> stmtToVars = extractor.getStmtToVarsMap();
    std::unordered_map<string, unordered_set<string>> procToVars = extractor.getProcToVarsMap();

    // expected
    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {1, {"y"}}, {2, {"y"}}, {3, {"y"}}, {4, {"y"}}, {5, {"y"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"p1", {"y"}}, {"p2", {"y"}}, {"p3", {"y"}}, {"p4", {"y"}}, {"p5", {"y"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Uses between (Multi-Procedure Calls) - all used variables of a procedure should be used by "
          "the parent container statement of the calling stmt of that procedure",
          "[UsesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    UsesRelationshipExtractor extractor{pkbAdapter};
    // Code:
    /*
    Procedure A {
    1	while (1 == 1) {
    2		while (1==1) {
    3			call B;
            }
        }
    }

    Procedure B {
    4	print x
    }

    Procedure C {
    5	while (1==1) {
    6		call A;
        }
    7	while {0 == 0) {…}
    }
    */
    auto programNode = MockASTs::MultiProcedureCalls::mock2();
    extractor.extractRelationship(programNode);
    std::unordered_map<int, unordered_set<string>> stmtToVars = extractor.getStmtToVarsMap();
    std::unordered_map<string, unordered_set<string>> procToVars = extractor.getProcToVarsMap();

    // expected
    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {1, {"x"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x"}}, {6, {"x"}}, {7, {"x"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"A", {"x"}},
        {"B", {"x"}},
        {"C", {"x"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Uses between (Multi-Procedure Calls) - moderate", "[UsesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    UsesRelationshipExtractor extractor{pkbAdapter};
    // Code:
    /*
        Procedure A {
    1        print x;
    2        if (y < 0) {
    3            print y;
    4            call B;
            } else {
    5            while (z == 0) {
    6                print w;
    7                call C;
                }
            }
        }

    Procedure B {
        8       call D;
    }

    Procedure C {
        9        read i;
    }

    Procedure D {
        10      print m;
        11      call C
    };
    */
    auto programNode = MockASTs::MultiProcedureCalls::mock3();
    extractor.extractRelationship(programNode);
    std::unordered_map<int, unordered_set<string>> stmtToVars = extractor.getStmtToVarsMap();
    std::unordered_map<string, unordered_set<string>> procToVars = extractor.getProcToVarsMap();

    // expected
    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {1, {"x"}},  {2, {"y", "z", "w", "m"}}, {3, {"y"}}, {4, {"m"}}, {5, {"z", "w"}}, {6, {"w"}}, {8, {"m"}},
        {10, {"m"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"A", {"x", "y", "z", "w", "m"}},
        {"B", {"m"}},
        {"D", {"m"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}
