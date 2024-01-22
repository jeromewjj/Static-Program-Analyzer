#include "PKB/Utils/StarRelationshipUtil.h"
#include "catch.hpp"

namespace std {
    template <typename T, typename U> struct hash<pair<T, U>> {
        size_t operator()(const pair<T, U>& p) const {
            auto h1 = std::hash<T>{}(p.first);
            auto h2 = std::hash<U>{}(p.second);

            // Combine the hash values using a simple hashCombine function
            return h1 ^ (h2 << 1);
        }
    };
}

TEST_CASE("StarRelationshipUtil - GenerateStarRelations") {
    StarRelationshipUtil<std::string>::PairSet standardRelations{std::make_pair("A", "B"), std::make_pair("B", "C"),
                                                                 std::make_pair("C", "D"), std::make_pair("D", "E")};

    StarRelationshipUtil<std::string>::PairSet expectedRelations{
        std::make_pair("A", "B"), std::make_pair("A", "C"), std::make_pair("A", "D"), std::make_pair("A", "E"),
        std::make_pair("B", "C"), std::make_pair("B", "D"), std::make_pair("B", "E"), std::make_pair("C", "D"),
        std::make_pair("C", "E"), std::make_pair("D", "E")};

    StarRelationshipUtil<std::string>::PairSet result =
        StarRelationshipUtil<std::string>::GenerateStarRelations(standardRelations);

    REQUIRE(result == expectedRelations);
}

TEST_CASE("StarRelationshipUtil - GenerateStarRelations Empty Input") {
    StarRelationshipUtil<int>::PairSet standardRelations;

    StarRelationshipUtil<int>::PairSet expectedRelations;

    StarRelationshipUtil<int>::PairSet result = StarRelationshipUtil<int>::GenerateStarRelations(standardRelations);

    REQUIRE(result == expectedRelations);
}

TEST_CASE("StarRelationshipUtil - GenerateStarRelations Single Element") {
    StarRelationshipUtil<char>::PairSet standardRelations{std::make_pair('A', 'B')};

    StarRelationshipUtil<char>::PairSet expectedRelations{std::make_pair('A', 'B')};

    StarRelationshipUtil<char>::PairSet result = StarRelationshipUtil<char>::GenerateStarRelations(standardRelations);

    REQUIRE(result == expectedRelations);
}

TEST_CASE("StarRelationshipUtil - GenerateStarRelations Additional Test Cases") {
    // Test case with cycles
    StarRelationshipUtil<std::string>::PairSet relationsWithCycle{std::make_pair("A", "B"), std::make_pair("B", "C"),
                                                                  std::make_pair("C", "A"), std::make_pair("D", "E")};

    StarRelationshipUtil<std::string>::PairSet expectedCycleRelations{
        std::make_pair("A", "A"), std::make_pair("A", "B"), std::make_pair("A", "C"), std::make_pair("B", "B"),
        std::make_pair("B", "C"), std::make_pair("B", "A"), std::make_pair("C", "C"), std::make_pair("C", "A"),
        std::make_pair("C", "B"), std::make_pair("D", "E"),
    };

    StarRelationshipUtil<std::string>::PairSet resultCycle =
        StarRelationshipUtil<std::string>::GenerateStarRelations(relationsWithCycle);
    REQUIRE(resultCycle == expectedCycleRelations);

    // Test case with no transitive relations
    StarRelationshipUtil<int>::PairSet noTransitiveRelations{std::make_pair(1, 2), std::make_pair(3, 4),
                                                             std::make_pair(5, 6)};

    StarRelationshipUtil<int>::PairSet expectedNoTransitiveRelations{std::make_pair(1, 2), std::make_pair(3, 4),
                                                                     std::make_pair(5, 6)};

    StarRelationshipUtil<int>::PairSet resultNoTransitive =
        StarRelationshipUtil<int>::GenerateStarRelations(noTransitiveRelations);
    REQUIRE(resultNoTransitive == expectedNoTransitiveRelations);

    // Test case with duplicate relations
    StarRelationshipUtil<char>::PairSet duplicateRelations{std::make_pair('A', 'B'), std::make_pair('B', 'C'),
                                                           std::make_pair('C', 'D'), std::make_pair('A', 'B'),
                                                           std::make_pair('B', 'C')};

    StarRelationshipUtil<char>::PairSet expectedDuplicateRelations{std::make_pair('A', 'B'), std::make_pair('A', 'C'),
                                                                   std::make_pair('A', 'D'), std::make_pair('B', 'C'),
                                                                   std::make_pair('B', 'D'), std::make_pair('C', 'D')};

    StarRelationshipUtil<char>::PairSet resultDuplicate =
        StarRelationshipUtil<char>::GenerateStarRelations(duplicateRelations);
    REQUIRE(resultDuplicate == expectedDuplicateRelations);
}
