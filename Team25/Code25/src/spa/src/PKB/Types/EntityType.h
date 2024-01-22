#pragma once

#include <string>

#include "StatementType.h"

class EntityTypes {
public:
    /**
     * Wrapper alias around string to represent a procedure.
     */
    using PROCEDURE = std::string;

    /**
     * Wrapper alias around string to represent a variable.
     */
    using VARIABLE = std::string;

    /**
     * Wrapper alias around string to represent a constant.
     */
    using CONSTANT = std::string;

    /**
     * Wrapper alias around int to represent a statement number.
     */
    using STATEMENT_NUMBER = int;

    /**
     * Wrapper alias around struct Statement to represent a statement.
     */
    struct STATEMENT {
        StatementType type;
        STATEMENT_NUMBER stmtNum;

        // Define a member function to compute the hash for the STATEMENT
        [[nodiscard]] std::size_t hash() const {
            std::size_t hash_value = 0;

            // Combine hash values of struct members
            hash_value ^= std::hash<int>()(static_cast<int>(type));
            hash_value ^= std::hash<STATEMENT_NUMBER>()(stmtNum);

            return hash_value;
        }

        // Define an equality operator for the STATEMENT
        bool operator==(const STATEMENT& other) const {
            return (type == other.type) && (stmtNum == other.stmtNum);
        }
    };

    /**
     * Wrapper alias around size_t for a key to map a value to.
     */
    using KEY = std::size_t;
};

namespace std {
    template <> struct hash<EntityTypes::STATEMENT> {
        std::size_t operator()(const EntityTypes::STATEMENT& stmt) const {
            return stmt.hash();
        }
    };
}
