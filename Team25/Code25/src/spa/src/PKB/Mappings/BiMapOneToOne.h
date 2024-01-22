#pragma once

#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "PKB/Utils/PairHashUtil.h"

/**
 * @class BiMapOneToOne
 * @brief A bidirectional map that enforces one-to-one mapping between keys and values.
 *
 * The BiMapOneToOne class allows you to establish a bidirectional mapping where each key
 * maps to a unique value, and each value maps to a unique key. Duplicate keys or values
 * are not allowed.
 *
 * @tparam Key The type of the keys in the mapping.
 * @tparam Value The type of the values in the mapping.
 */
template <typename Key, typename Value> class BiMapOneToOne {
private:
    std::unordered_map<Key, Value> forwardMap;
    std::unordered_map<Value, Key> reverseMap;
    std::unordered_set<std::pair<Key, Value>, PairHash<Key, Value>> pairSet;
    std::unordered_set<Key> keySet;
    std::unordered_set<Value> valueSet;
    std::size_t size = 0;

public:
    // Constructor
    BiMapOneToOne();

    // Insert a mapping from key to value
    void insert(Key key, Value value);

    // Get the value associated with a key
    Value getValue(Key key);

    // Get the key associated with a value
    Key getKey(Value value);

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

#include "BiMapOneToOne.tpp"
