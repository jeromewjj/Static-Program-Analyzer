#include "PKB/Mappings/BiMapManyToMany.h"
#include "catch.hpp"

TEST_CASE("Insertion and retrieval of key-value pairs") {
    BiMapManyToMany<int, std::string> biMap;

    // Insert key-value pairs
    biMap.insert(1, "apple");
    biMap.insert(1, "banana");
    biMap.insert(2, "cherry");

    SECTION("Retrieve values associated with a key") {
        std::unordered_set<std::string> values = biMap.getValues(1);
        REQUIRE(values.size() == 2);
        REQUIRE(values.count("apple") == 1);
        REQUIRE(values.count("banana") == 1);
    }

    SECTION("Retrieve keys associated with a value") {
        std::unordered_set<int> keys = biMap.getKeys("cherry");
        REQUIRE(keys.size() == 1);
        REQUIRE(keys.count(2) == 1);
    }

    SECTION("Check length") {
        REQUIRE(biMap.length() == 3);
    }
}

TEST_CASE("Check for key and value existence") {
    BiMapManyToMany<int, std::string> biMap;

    biMap.insert(1, "apple");
    biMap.insert(2, "banana");

    SECTION("Check if a key exists") {
        REQUIRE(biMap.containsKey(1) == true);
        REQUIRE(biMap.containsKey(3) == false);
    }

    SECTION("Check if a value exists") {
        REQUIRE(biMap.containsValue("apple") == true);
        REQUIRE(biMap.containsValue("cherry") == false);
    }

    SECTION("Check length") {
        REQUIRE(biMap.length() == 2);
    }
}

TEST_CASE("Retrieve all keys and values") {
    BiMapManyToMany<int, std::string> biMap;

    biMap.insert(1, "apple");
    biMap.insert(2, "banana");
    biMap.insert(3, "cherry");

    SECTION("Retrieve all keys") {
        std::unordered_set<int> keys = biMap.getAllKeys();
        REQUIRE(keys.size() == 3);
        REQUIRE(keys.count(1) == 1);
        REQUIRE(keys.count(2) == 1);
        REQUIRE(keys.count(3) == 1);
    }

    SECTION("Retrieve non existent key") {
        std::unordered_set<int> keys = biMap.getKeys("pear");
        REQUIRE(keys.empty());
    }

    SECTION("Retrieve all values") {
        std::unordered_set<std::string> values = biMap.getAllValues();
        REQUIRE(values.size() == 3);
        REQUIRE(values.count("apple") == 1);
        REQUIRE(values.count("banana") == 1);
        REQUIRE(values.count("cherry") == 1);
    }

    SECTION("Retrieve non existent value") {
        std::unordered_set<std::string> values = biMap.getValues(7);
        REQUIRE(values.empty());
    }

    SECTION("Check length") {
        REQUIRE(biMap.length() == 3);
    }
}

TEST_CASE("Check for key-value pair existence") {
    BiMapManyToMany<int, std::string> biMap;

    biMap.insert(1, "apple");
    biMap.insert(2, "banana");

    SECTION("Check if a key-value pair exists") {
        REQUIRE(biMap.containsKeyValuePair(1, "apple") == true);
        REQUIRE(biMap.containsKeyValuePair(1, "banana") == false);
        REQUIRE(biMap.containsKeyValuePair(2, "banana") == true);
    }

    SECTION("Check length") {
        REQUIRE(biMap.length() == 2);
    }
}
