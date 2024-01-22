#pragma once

#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "PKB/Utils/PairHashUtil.h"

/**
 * @class BiMapManyToMany
 * @brief A bidirectional map that enforces many-to-many mapping between keys and values.
 *
 * The BiMapManyToMany class allows you to establish a bidirectional mapping where each key
 * can be maps to multiple values, and each value can be maps to multiple keys.
 *
 * @tparam Key The type of the keys in the mapping.
 * @tparam Value The type of the values in the mapping.
 */
template <typename Key, typename Value> class BiMapManyToMany {
private:
    std::unordered_map<Key, std::unordered_set<Value>> forwardMap;
    std::unordered_map<Value, std::unordered_set<Key>> reverseMap;
    std::unordered_set<std::pair<Key, Value>, PairHash<Key, Value>> pairSet;
    std::unordered_set<Key> keySet;
    std::unordered_set<Value> valueSet;
    std::size_t size = 0;

public:
    // Constructor
    BiMapManyToMany();

    // Insert a key-value mapping
    void insert(Key key, Value value);

    // Get all values associated with a key
    std::unordered_set<Value> getValues(Key key);

    // Get all keys associated with a value
    std::unordered_set<Key> getKeys(Value value);

    // Get all keys
    std::unordered_set<Key> getAllKeys();

    // Get all values
    std::unordered_set<Value> getAllValues();

    // Check if a key is in the map
    bool containsKey(Key key);

    // Check if a value is in the map
    bool containsValue(Value value);

    // Check if key value pair is in the map
    bool containsKeyValuePair(Key key, Value value);

    // Retrieves the number of relations in the map
    std::size_t length();
};

#include "BiMapManyToMany.tpp"
