#pragma once
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "SP/AST/ASTNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/AST/VariableNode.h"

namespace Helper {
    std::unordered_map<std::string, std::unordered_set<std::string>>
    getTransitiveClosure(std::unordered_map<std::string, std::unordered_set<std::string>> s);

    template <typename K, typename V>
    std::unordered_map<V, std::unordered_set<K>> reverseMap(std::unordered_map<K, std::unordered_set<V>> map) {
        std::unordered_map<V, std::unordered_set<K>> res{};
        for (const std::pair<K, std::unordered_set<V>>& item : map) {
            const K key = item.first;
            for (const V& value : item.second) {
                res[value].insert(key);
            }
        }
        return res;
    }

    std::unordered_set<std::string> getVarNamesInSubtree(const ASTNodePtr_VIEWONLY& node);
};
