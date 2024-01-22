#pragma once

#include <string>
#include <unordered_set>
#include <utility>

#include "EntityType.h"

struct Assign {
    EntityTypes::STATEMENT_NUMBER stmtNum;
    // LHS variable
    EntityTypes::VARIABLE var;
    // Exact Expression
    std::string exactExp;
    // Set of partial expression including the exact expression
    std::unordered_set<std::string> partialExpSet;

    // Define a member function to compute the hash for the Assign
    [[nodiscard]] std::size_t hash() const {
        std::size_t hash_value = 0;

        // Add hash values of stmtNum
        hash_value ^= std::hash<int>()(static_cast<int>(stmtNum));

        return hash_value;
    }

    // Define an equality operator for the Assign
    bool operator==(const Assign& other) const {
        return stmtNum == other.stmtNum;
    }
};

namespace std {
    template <> struct hash<Assign> {
        std::size_t operator()(const Assign& obj) const {
            return obj.hash();
        }
    };
}
