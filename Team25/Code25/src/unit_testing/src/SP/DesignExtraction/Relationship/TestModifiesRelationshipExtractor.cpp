#include "../../AST/MockASTs.h"
#include "SP/DesignExtraction/Relationship/ModifiesRelationshipExtractor.h"
#include "catch.hpp"

TEST_CASE("Should extract Modifies of different types (Single-Procedure)", "[ModifiesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    ModifiesRelationshipExtractor extractor{pkbAdapter};

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
    //   } else {
    //7     print x;
    //   }
    // }
    */
    // Modified Vars:
    /*
     * 1:x
     * 2:x
     * 3:x
     * 4:y
     *
     * p: x,y
     */

    auto progNode = MockASTs::mock2();
    extractor.extractRelationship(progNode);
    std::unordered_map<int, unordered_set<string>> stmtToVars = extractor.getStmtToVarsMap();
    std::unordered_map<string, unordered_set<string>> procToVars = extractor.getProcToVarsMap();

    // expected
    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {1, {"x"}}, {2, {"x"}}, {3, {"x"}}, {4, {"y"}}};
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"p", {"x", "y"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Modifies (Multi-Procedure Calls) - simple", "[ModifiesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    ModifiesRelationshipExtractor extractor{pkbAdapter};
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
        {1, {"x"}},
        {2, {"x"}},
        {3, {"x"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"p1", {"x"}},
        {"p2", {"x"}},
        {"p3", {"x"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Modifes between (Multi-Procedure Calls) - long chain", "[ModifiesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    ModifiesRelationshipExtractor extractor{pkbAdapter};
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

    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {1, {"x"}}, {2, {"x"}}, {3, {"x"}}, {4, {"x"}}, {5, {"x"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"p1", {"x"}}, {"p2", {"x"}}, {"p3", {"x"}}, {"p4", {"x"}}, {"p5", {"x"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Modifies between (Multi-Procedure Calls) - all modified variables of a procedure should be "
          "said to be modified by the parent container statement of the calling stmt of that procedure",
          "[ModifiesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    ModifiesRelationshipExtractor extractor{pkbAdapter};
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
    5   read y
    }

    Procedure C {
    6	while (1==1) {
    7		call A;
        }
    }
    */
    auto programNode = MockASTs::MultiProcedureCalls::mock2();
    extractor.extractRelationship(programNode);
    std::unordered_map<int, unordered_set<string>> stmtToVars = extractor.getStmtToVarsMap();
    std::unordered_map<string, unordered_set<string>> procToVars = extractor.getProcToVarsMap();

    // expected
    std::unordered_map<int, std::unordered_set<string>> EXPECTED_STMT_TO_VARS{
        {1, {"y"}}, {2, {"y"}}, {3, {"y"}}, {5, {"y"}}, {6, {"y"}}, {7, {"y"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"A", {"y"}},
        {"B", {"y"}},
        {"C", {"y"}},
    };

    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}

TEST_CASE("Should extract Modifies between (Multi-Procedure Calls) - moderate", "[ModifiesRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    ModifiesRelationshipExtractor extractor{pkbAdapter};
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
        {2, {"i"}}, {4, {"i"}}, {5, {"i"}}, {7, {"i"}}, {8, {"i"}}, {9, {"i"}}, {11, {"i"}},
    };
    std::unordered_map<string, std::unordered_set<string>> EXPECTED_PROC_TO_VARS{
        {"A", {"i"}}, {"B", {"i"}}, {"C", {"i"}}, {"D", {"i"}}};
    REQUIRE(stmtToVars == EXPECTED_STMT_TO_VARS);
    REQUIRE(procToVars == EXPECTED_PROC_TO_VARS);
}