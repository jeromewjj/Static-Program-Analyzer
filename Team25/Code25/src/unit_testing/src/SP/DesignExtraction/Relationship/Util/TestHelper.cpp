#include "SP/DesignExtraction/Relationship/Util/Helper.h"
#include "catch.hpp"

using std::string;
using std::unordered_map;
using std::unordered_set;

TEST_CASE("Simple Transitive Closure", "[Helper]") {
    unordered_map<string, unordered_set<string>> xy{
        {"a", {"b"}},
        {"b", {"c"}},
    };

    unordered_map<string, unordered_set<string>> EXPECTED_XY{
        {"a", {"b", "c"}},
        {"b", {"c"}},
    };

    auto transitiveClosure = Helper::getTransitiveClosure(xy);
    REQUIRE(transitiveClosure == EXPECTED_XY);
}

TEST_CASE("No Transitive Closure (Empty)", "[Helper]") {
    unordered_map<string, unordered_set<string>> ab{
        {"a", {"b"}},
        {"b", {}},
    };

    unordered_map<string, unordered_set<string>> EXPECTED_AB{
        {"a", {"b"}},
        {"b", {}},
    };

    auto transitiveClosure = Helper::getTransitiveClosure(ab);
    REQUIRE(transitiveClosure == EXPECTED_AB);
}

TEST_CASE("Multiple Layers of Transitive Closure", "[Helper]") {
    unordered_map<string, unordered_set<string>> xyz{
        {"a", {"b"}},
        {"b", {"c"}},
        {"c", {"d"}},
    };

    unordered_map<string, unordered_set<string>> EXPECTED_XYZ{
        {"a", {"b", "c", "d"}},
        {"b", {"c", "d"}},
        {"c", {"d"}},
    };

    auto transitiveClosure = Helper::getTransitiveClosure(xyz);
    REQUIRE(transitiveClosure == EXPECTED_XYZ);
}

TEST_CASE("Cyclic Dependency", "[Helper]") {
    unordered_map<string, unordered_set<string>> cyclical{
        {"a", {"b"}},
        {"b", {"c"}},
        {"c", {"a"}},
    };

    unordered_map<string, unordered_set<string>> EXPECTED_CYCLICAL{
        {"a", {"a", "b", "c"}},
        {"b", {"a", "b", "c"}},
        {"c", {"a", "b", "c"}},
    };

    auto transitiveClosure = Helper::getTransitiveClosure(cyclical);
    REQUIRE(transitiveClosure == EXPECTED_CYCLICAL);
}
