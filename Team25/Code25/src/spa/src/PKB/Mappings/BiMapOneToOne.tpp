template <typename Key, typename Value> BiMapOneToOne<Key, Value>::BiMapOneToOne() = default;

template <typename Key, typename Value> void BiMapOneToOne<Key, Value>::insert(Key key, Value value) {
    forwardMap[key] = value;
    reverseMap[value] = key;
    pairSet.insert({key, value});
    keySet.insert(key);
    valueSet.insert(value);
    this->size++;
}

template <typename Key, typename Value> Value BiMapOneToOne<Key, Value>::getValue(Key key) {
    if (forwardMap.find(key) != forwardMap.end()) {
        return forwardMap.at(key);
    }
    else {
        return Value();
    }
}

template <typename Key, typename Value> Key BiMapOneToOne<Key, Value>::getKey(Value value) {
    if (reverseMap.find(value) != reverseMap.end()) {
        return reverseMap.at(value);
    }
    else {
        return Key();
    }
}

template <typename Key, typename Value> std::unordered_set<Key> BiMapOneToOne<Key, Value>::getAllKeys() {
    return keySet;
}

template <typename Key, typename Value> std::unordered_set<Value> BiMapOneToOne<Key, Value>::getAllValues() {
    return valueSet;
}

template <typename Key, typename Value> bool BiMapOneToOne<Key, Value>::containsKey(Key key) {
    return keySet.find(key) != keySet.end();
}

template <typename Key, typename Value> bool BiMapOneToOne<Key, Value>::containsValue(Value value) {
    return valueSet.find(value) != valueSet.end();
}

template <typename Key, typename Value> std::size_t BiMapOneToOne<Key, Value>::length() {
    return this->size;
}

template <typename Key, typename Value> bool BiMapOneToOne<Key, Value>::containsKeyValuePair(Key key, Value value) {
    return pairSet.find({key, value}) != pairSet.end();
}
