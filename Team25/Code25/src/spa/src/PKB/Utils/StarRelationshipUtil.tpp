// Implementation of the GetStarRelations method
template <typename Type>
typename StarRelationshipUtil<Type>::PairSet StarRelationshipUtil<Type>::GenerateStarRelations(const PairSet& pairSet) {
    EntityIndexMap entityToIndexMap;
    int index = 0;

    BuildEntityToIndexMap(pairSet, entityToIndexMap, index);
    TransitiveMatrix directRelations = BuildDirectRelations(entityToIndexMap, pairSet);
    TransitiveMatrix transitiveClosure = ComputeTransitiveClosure(entityToIndexMap, directRelations);

    PairSet result = ExtractTransitiveRelations(entityToIndexMap, transitiveClosure);

    return result;
}

// Build the entityToIndexMap
template <typename Type>
void StarRelationshipUtil<Type>::BuildEntityToIndexMap(const PairSet& pairSet, EntityIndexMap& entityToIndexMap,
                                                       int& index) {
    for (const auto& p : pairSet) {
        if (entityToIndexMap.find(p.first) == entityToIndexMap.end()) {
            entityToIndexMap[p.first] = index++;
        }
        if (entityToIndexMap.find(p.second) == entityToIndexMap.end()) {
            entityToIndexMap[p.second] = index++;
        }
    }
}

// Build the directRelations matrix
template <typename Type>
typename StarRelationshipUtil<Type>::TransitiveMatrix
StarRelationshipUtil<Type>::BuildDirectRelations(const EntityIndexMap& entityToIndexMap, const PairSet& pairSet) {
    int index = entityToIndexMap.size();
    TransitiveMatrix directRelations(index, std::vector<bool>(index, false));

    for (const auto& p : pairSet) {
        int i = entityToIndexMap.at(p.first);
        int j = entityToIndexMap.at(p.second);
        directRelations[i][j] = true;
    }

    return directRelations;
}

// Extract transitive relations from the closure matrix
template <typename Type>
typename StarRelationshipUtil<Type>::PairSet
StarRelationshipUtil<Type>::ExtractTransitiveRelations(const EntityIndexMap& entityToIndexMap,
                                                       const TransitiveMatrix& transitiveClosure) {
    PairSet result;

    for (const auto& entry : entityToIndexMap) {
        Type a = entry.first;
        int i = entry.second;
        for (const auto& sub_entry : entityToIndexMap) {
            Type b = sub_entry.first;
            int j = sub_entry.second;
            if (transitiveClosure[i][j]) {
                result.insert(std::make_pair(a, b));
            }
        }
    }

    return result;
}

// Implementation of the ComputeTransitiveClosure method
template <typename Type>
typename StarRelationshipUtil<Type>::TransitiveMatrix
StarRelationshipUtil<Type>::ComputeTransitiveClosure(const EntityIndexMap& entityToIndex,
                                                     const TransitiveMatrix& directRelations) {
    int size = entityToIndex.size();
    TransitiveMatrix closure(size, std::vector<bool>(size, false));

    // Initialize the closure matrix with direct relations
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            closure[i][j] = directRelations[i][j];
        }
    }

    // Floyd-Warshall algorithm for transitive closure
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }

    return closure;
}