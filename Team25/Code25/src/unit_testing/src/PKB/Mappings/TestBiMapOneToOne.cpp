#include "PKB/Mappings/BiMapOneToOne.h"
#include "catch.hpp"

TEST_CASE("Test BiMapOneToOne operations", "[BiMapOneToOne]") {
    BiMapOneToOne<int, std::string> bimap;

    SECTION("Insert and retrieve values") {
        REQUIRE(bimap.length() == 0);
        bimap.insert(1, "One");
        bimap.insert(2, "Two");

        REQUIRE(bimap.getValue(1) == "One");
        REQUIRE(bimap.getKey("Two") == 2);
        REQUIRE(bimap.getAllValues() == std::unordered_set<std::string>({"One", "Two"}));
        REQUIRE(bimap.getAllKeys() == std::unordered_set<int>({1, 2}));

        // Get non existent key
        REQUIRE(bimap.getValue(3).empty());
        // Get non existent value
        REQUIRE(bimap.getKey("Three") == int());
        REQUIRE(bimap.length() == 2);
    }

    SECTION("Check containment") {
        REQUIRE(bimap.length() == 0);
        bimap.insert(3, "Three");
        bimap.insert(4, "Four");

        REQUIRE(bimap.containsKey(3) == true);
        REQUIRE(bimap.containsValue("Four") == true);
        REQUIRE(bimap.containsKey(5) == false);
        REQUIRE(bimap.containsValue("Five") == false);
        REQUIRE(bimap.containsKeyValuePair(3, "Four") == false);
        REQUIRE(bimap.containsKeyValuePair(3, "Three") == true);
        REQUIRE(bimap.length() == 2);
    }
}
