#include "../../AST/MockASTs.h"
#include "SP/DesignExtraction/Relationship/ParentsRelationshipExtractor.h"
#include "catch.hpp"

TEST_CASE("Should extract Parents from If and While [1 layer nesting]", "[ParentsRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    ParentsRelationshipExtractor p_x{pkbAdapter};

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
    auto p = MockASTs::mock2();
    p_x.extractRelationship(p);
    auto parentsSet = p_x.getParentChildSet();

    // expected
    std::unordered_set<std::pair<int, int>> EXPECTED_PARENTS_SET{{2, 3}, {5, 6}, {5, 7}};

    //    for (auto &x: EXPECTED_PARENTS_SET) {
    //        std::cout << x.first << "," << x.second << std::endl;
    //    }
    //    for (auto &x: *parentsSet) {
    //        std::cout << x.first << "," << x.second << std::endl;
    //    }
    REQUIRE(*parentsSet == EXPECTED_PARENTS_SET);
}