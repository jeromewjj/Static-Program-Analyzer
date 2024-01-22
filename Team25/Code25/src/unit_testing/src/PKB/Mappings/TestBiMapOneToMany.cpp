#include "PKB/Mappings/BiMapOneToMany.h"
#include "catch.hpp"

TEST_CASE("Test BiMapOneToMany") {
    SECTION("Test insert and getValues") {
        BiMapOneToMany<int, std::string> biMap;

        REQUIRE(biMap.length() == 0);

        biMap.insert(1, "One");
        biMap.insert(2, "Two");
        biMap.insert(1, "Uno");

        REQUIRE(biMap.getValues(1) == std::unordered_set<std::string>{"One", "Uno"});
        REQUIRE(biMap.getValues(2) == std::unordered_set<std::string>{"Two"});

        // Test inserting a key-value pair
        biMap.insert(3, "Three");
        REQUIRE(biMap.getValues(3) == std::unordered_set<std::string>{"Three"});

        // Test get value that is not found

        REQUIRE(biMap.getValues(4) == std::unordered_set<std::string>{});
        REQUIRE(biMap.length() == 4);
    }

    SECTION("Test getKey") {
        BiMapOneToMany<int, std::string> biMap;
        REQUIRE(biMap.length() == 0);

        biMap.insert(1, "One");
        biMap.insert(2, "Two");
        biMap.insert(1, "Uno");

        REQUIRE(biMap.getKey("One") == 1);
        REQUIRE(biMap.getKey("Two") == 2);
        REQUIRE(biMap.getKey("Uno") == 1);
        REQUIRE(biMap.getKey("Duo") == int());

        // Test getting keys for a non-existent value
        REQUIRE(biMap.getKey("Three") == int());
        REQUIRE(biMap.length() == 3);
    }
    SECTION("Test getAllKeys") {
        BiMapOneToMany<int, std::string> biMap;

        REQUIRE(biMap.length() == 0);

        biMap.insert(1, "One");
        biMap.insert(2, "Two");
        biMap.insert(3, "Three");

        REQUIRE(biMap.getAllKeys() == std::unordered_set<int>{1, 2, 3});

        REQUIRE(biMap.length() == 3);
    }

    SECTION("Test getAllValues") {
        BiMapOneToMany<int, std::string> biMap;

        REQUIRE(biMap.length() == 0);

        biMap.insert(1, "One");
        biMap.insert(2, "Two");
        biMap.insert(3, "Three");

        REQUIRE(biMap.getAllValues() == std::unordered_set<std::string>{"One", "Two", "Three"});
        REQUIRE(biMap.length() == 3);
    }

    SECTION("Test containsKey") {
        BiMapOneToMany<int, std::string> biMap;

        REQUIRE(biMap.length() == 0);

        biMap.insert(1, "One");
        biMap.insert(2, "Two");

        REQUIRE(biMap.containsKey(1) == true);
        REQUIRE(biMap.containsKey(2) == true);
        REQUIRE(biMap.containsKey(3) == false);

        REQUIRE(biMap.length() == 2);
    }

    SECTION("Test containsValue") {
        BiMapOneToMany<int, std::string> biMap;
        REQUIRE(biMap.length() == 0);

        biMap.insert(1, "One");
        biMap.insert(2, "Two");

        REQUIRE(biMap.containsValue("One") == true);
        REQUIRE(biMap.containsValue("Two") == true);
        REQUIRE(biMap.containsValue("Three") == false);
        REQUIRE(biMap.length() == 2);
    }

    SECTION("Test containsKeyValuePair") {
        BiMapOneToMany<int, std::string> biMap;
        REQUIRE(biMap.length() == 0);

        biMap.insert(1, "One");
        biMap.insert(2, "Two");
        biMap.insert(1, "Uno");

        REQUIRE(biMap.containsKeyValuePair(1, "One") == true);
        REQUIRE(biMap.containsKeyValuePair(1, "Two") == false);
        REQUIRE(biMap.containsKeyValuePair(2, "Two") == true);
        REQUIRE(biMap.containsKeyValuePair(3, "Three") == false);
        REQUIRE(biMap.length() == 3);
    }
}