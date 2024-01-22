#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename Type> class StarRelationshipUtil {
public:
    using EntityIndexMap = std::unordered_map<Type, int>;
    using PairSet = std::unordered_set<std::pair<Type, Type>>;
    using TransitiveMatrix = std::vector<std::vector<bool>>;

    static PairSet GenerateStarRelations(const PairSet& pairSet);

private:
    static TransitiveMatrix ComputeTransitiveClosure(const EntityIndexMap& entityToIndex,
                                                     const TransitiveMatrix& directRelations);
    static void BuildEntityToIndexMap(const PairSet& pairSet, EntityIndexMap& entityToIndexMap, int& index);
    static TransitiveMatrix BuildDirectRelations(const EntityIndexMap& entityToIndexMap, const PairSet& pairSet);
    static PairSet ExtractTransitiveRelations(const EntityIndexMap& entityToIndexMap,
                                              const TransitiveMatrix& transitiveClosure);
};

#include "StarRelationshipUtil.tpp"
