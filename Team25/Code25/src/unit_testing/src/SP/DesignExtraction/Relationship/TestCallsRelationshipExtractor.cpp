#include "../../AST/MockASTs.h"
#include "SP/DesignExtraction/Relationship/CallsRelationshipExtractor.h"
#include "catch.hpp"

TEST_CASE("Should extract from Call nodes", "[CallsRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    CallsRelationshipExtractor c_x{pkbAdapter};

    auto rootNode = MockASTs::mock3();
    c_x.extractRelationship(rootNode);
    auto callsSet = c_x.getCallsSet();

    // expected
    unordered_set<pair<string, string>> EXPECTED_CALLS_SET{{"p1", "p2"}, {"p1", "p3"}, {"p3", "p2"}};

    REQUIRE(*callsSet == EXPECTED_CALLS_SET);
}

TEST_CASE("Should not extract when there are no Call nodes", "[CallsRelationshipExtractor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    CallsRelationshipExtractor c_x{pkbAdapter};

    auto rootNode = MockASTs::mock2();
    c_x.extractRelationship(rootNode);
    auto callsSet = c_x.getCallsSet();

    // expected
    unordered_set<pair<string, string>> EXPECTED_CALLS_SET{};

    REQUIRE(*callsSet == EXPECTED_CALLS_SET);
}