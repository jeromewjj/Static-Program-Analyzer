template <typename Key, typename Value> BiMapManyToMany<Key, Value>::BiMapManyToMany() = default;

template <typename Key, typename Value> void BiMapManyToMany<Key, Value>::insert(Key key, Value value) {
    forwardMap[key].insert(value);
    reverseMap[value].insert(key);
    pairSet.insert({key, value});
    keySet.insert(key);
    valueSet.insert(value);
    this->size++;
}

template <typename Key, typename Value> std::unordered_set<Value> BiMapManyToMany<Key, Value>::getValues(Key key) {
    if (forwardMap.find(key) != forwardMap.end()) {
        return forwardMap.at(key);
    }
    else {
        return std::unordered_set<Value>();
    }
}

template <typename Key, typename Value> std::unordered_set<Key> BiMapManyToMany<Key, Value>::getKeys(Value value) {
    if (reverseMap.find(value) != reverseMap.end()) {
        return reverseMap.at(value);
    }
    else {
        return std::unordered_set<Key>();
    }
}

template <typename Key, typename Value> std::unordered_set<Key> BiMapManyToMany<Key, Value>::getAllKeys() {
    return keySet;
}

template <typename Key, typename Value> std::unordered_set<Value> BiMapManyToMany<Key, Value>::getAllValues() {
    return valueSet;
}

template <typename Key, typename Value> bool BiMapManyToMany<Key, Value>::containsKey(Key key) {
    return keySet.find(key) != keySet.end();
}

template <typename Key, typename Value> bool BiMapManyToMany<Key, Value>::containsValue(Value value) {
    return valueSet.find(value) != valueSet.end();
}

template <typename Key, typename Value> bool BiMapManyToMany<Key, Value>::containsKeyValuePair(Key key, Value value) {
    return pairSet.find({key, value}) != pairSet.end();
}

template <typename Key, typename Value> std::size_t BiMapManyToMany<Key, Value>::length() {
    return this->size;
}
