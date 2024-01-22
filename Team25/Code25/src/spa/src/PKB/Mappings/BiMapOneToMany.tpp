template <typename Key, typename Value> BiMapOneToMany<Key, Value>::BiMapOneToMany() = default;

template <typename Key, typename Value> void BiMapOneToMany<Key, Value>::insert(Key key, Value value) {
    forwardMap[key].insert(value);
    reverseMap[value] = key;
    pairSet.insert({key, value});
    keySet.insert(key);
    valueSet.insert(value);
    this->size++;
}

template <typename Key, typename Value> std::unordered_set<Value> BiMapOneToMany<Key, Value>::getValues(Key key) {
    if (forwardMap.find(key) != forwardMap.end()) {
        return forwardMap[key];
    }
    else {
        return std::unordered_set<Value>();
    }
}

template <typename Key, typename Value> Key BiMapOneToMany<Key, Value>::getKey(Value value) {
    if (reverseMap.find(value) != reverseMap.end()) {
        return reverseMap[value];
    }
    else {

        return Key();
    }
}

template <typename Key, typename Value> std::unordered_set<Key> BiMapOneToMany<Key, Value>::getAllKeys() {
    return keySet;
}

template <typename Key, typename Value> std::unordered_set<Value> BiMapOneToMany<Key, Value>::getAllValues() {
    return valueSet;
}

template <typename Key, typename Value> bool BiMapOneToMany<Key, Value>::containsKey(Key key) {
    return keySet.find(key) != keySet.end();
}

template <typename Key, typename Value> bool BiMapOneToMany<Key, Value>::containsValue(Value value) {
    return valueSet.find(value) != valueSet.end();
}

template <typename Key, typename Value> bool BiMapOneToMany<Key, Value>::containsKeyValuePair(Key key, Value value) {
    return pairSet.find({key, value}) != pairSet.end();
}

template <typename Key, typename Value> std::size_t BiMapOneToMany<Key, Value>::length() {
    return this->size;
}