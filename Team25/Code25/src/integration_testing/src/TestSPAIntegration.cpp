#include <filesystem>

#include "PKB/PKB.h"
#include "catch.hpp"
#include "general/SPA.h"

/**
 *
 *
 *
        procedure Bumblebee {
1.          read x;
2.          read y;
3.          read z;
4.          if (x > 2) then {
5.              while (3 == 4) {
6.              x = 1 + x + y;
7.              y = x + 1;
8.              call Anya;
9.              z = x + 1;} }
            else {
10.          if (x == 5) then {
11.          x = 3 + y;
12.              while (x == y) {
13.                  y = 2 + x; } }
                else {
14.             y = x + 1;
15.             z = 3 + x; } }
        }

        procedure Anya {
16.         while (x == 0) {
17.             x = y + 1;
18.             if (b == a) then {
19.                     z = 7;
20.                     y = x + 1;
                    }
                else {
21.                 a = 3;
22.                 y = x;
23.                 x = y + z;
24.                 read y;
25.                 z = y + 1;
26.                 if (x==0) then {
27.                         a = x + 1;
28.                         y = a;
                        }
                    else {
29.                     a = y;
                    }
                }
            }
30.         y = 5 + x;
31.         x = 7;
        }
 *
 *
 *
 *
 *
 */
TEST_CASE("SPA Integration: bumblebee_source.txt") {
    PKB testPkb;
    SPA testSpa(testPkb);

    auto testDirectory = std::filesystem::path(INTEGRATION_TESTING_DIR);
    auto filePath = testDirectory.string() + "bumblebee_source.txt";

    testSpa.parse(filePath);

    SECTION("QPS-PKB Relation:Affects Get assign stmt") {
        std::string query = R"(
        assign a; Select a such that Affects(_,a))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"7", "22", "27", "13", "23", "30", "17", "28", "20"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next Get next stmt") {
        std::string query = R"(
        stmt s;
        Select BOOLEAN such that Next(15,_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"FALSE"};
        REQUIRE(stmtSet == expectedStmtSet);
    }

    SECTION("QPS-PKB Relation:Next* Get next stmt") {
        std::string query = R"(
        stmt s;
        Select BOOLEAN such that Next(15,_))";
        vector<string> result = testSpa.evaluate(query);
        std::unordered_set<string> stmtSet(result.begin(), result.end());

        std::unordered_set<string> expectedStmtSet = {"FALSE"};
        REQUIRE(stmtSet == expectedStmtSet);
    }
}
