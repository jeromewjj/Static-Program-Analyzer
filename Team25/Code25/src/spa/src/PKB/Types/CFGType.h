#pragma once

#include <string>
#include <unordered_set>

enum class CFGBlockType {
    START_PROC,
    END_PROC,
    END_WHILE,
    END_IF,
    NORMAL,
    WHILE,
    WHILE_THEN,
    IF,
    IF_THEN,
    IF_ELSE,
    DUMMY
};

/**
 * @brief Represents a cfg node in a program.
 *
 * @param id block id
 * @param proc procedure name it belong to
 * @param type CFGBlockType
 * @param stmtSet set of stmt number it contain
 * @param nextSet set of CFG Block id that
 */
struct CFGBlock {
    int id;
    const std::string proc;
    const CFGBlockType type;
    const std::unordered_set<int> stmtSet;
    const std::unordered_set<int> nextSet;

    // Define a member function to compute the hash for the STATEMENT
    [[nodiscard]] std::size_t hash() const {
        std::size_t hash_value = 0;

        // Combine hash values of struct memberspr
        hash_value ^= std::hash<int>()(static_cast<int>(id));
        hash_value ^= std::hash<std::string>()(static_cast<std::string>(proc));

        return hash_value;
    }

    // Define an equality operator for the STATEMENT
    bool operator==(const CFGBlock& other) const {
        return (id == other.id) && (type == other.type) && (type == other.type);
    }
};

namespace std {
    template <> struct hash<CFGBlock> {
        std::size_t operator()(const CFGBlock cfgBlock) const {
            return cfgBlock.hash();
        }
    };
}