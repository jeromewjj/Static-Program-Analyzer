#pragma once

#include "EntityType.h"

namespace std {
    template <typename T, typename U> struct hash<pair<T, U>> {
        size_t operator()(const pair<T, U>& p) const {
            auto h1 = std::hash<T>{}(p.first);
            auto h2 = std::hash<U>{}(p.second);

            // Combine the hash values using a simple hashCombine function
            return h1 ^ (h2 << 1);
        }
    };
}

using StmtNum = EntityTypes::STATEMENT_NUMBER;
using Procedure = EntityTypes::PROCEDURE;
using Variable = EntityTypes::VARIABLE;
using Constant = EntityTypes::CONSTANT;
using Statement = EntityTypes::STATEMENT;

class RelationshipTypes {
public:
    /**
     * Wrapper alias of Pair<FolloweeStmtNum, FollowerStmtNum> to represent a Follows Relationship.
     */
    using FOLLOWS_PAIR = std::pair<StmtNum, StmtNum>;

    /**
     * Wrapper alias of Pair<ParentStmtNum, ChildStmtNum> to represent a Parent Relationship.
     */
    using PARENT_PAIR = std::pair<StmtNum, StmtNum>;

    /**
     * Wrapper alias of Pair<StmtNums, Variable> to represent a Statement Uses Variable Relationship.
     */
    using STATEMENT_USES_PAIR = std::pair<StmtNum, Variable>;

    /**
     * Wrapper alias of Pair<Procedure, Variable> to represent a Procedure Uses Variable Relationship.
     */
    using PROCEDURE_USES_PAIR = std::pair<Procedure, Variable>;

    /**
     * Wrapper alias of Pair<StmtNums, Variable> to represent a Statement Modifies Variable Relationship.
     */
    using STATEMENT_MODIFIES_PAIR = std::pair<StmtNum, Variable>;

    /**
     * Wrapper alias of Pair<Procedure, Variable> to represent a Procedure Modifies Variable Relationship.
     */
    using PROCEDURE_MODIFIES_PAIR = std::pair<Procedure, Variable>;

    /**
     * Wrapper alias of Pair<Procedure, Procedure> to represent a Calls Relationship.
     */
    using CALLS_PAIR = std::pair<Procedure, Procedure>;

    /**
     * Wrapper alias of Pair<Procedure, StmtNum> to represent a Calls statement and procedure it is calling
     * Relationship.
     */
    using CALLS_STATEMENT_PAIR = std::pair<Procedure, StmtNum>;

    /**
     * Wrapper alias of Pair<Statement Number, Variable> to represent an if statement.
     */
    using If_PAIR = std::pair<StmtNum, Variable>;

    /**
     * Wrapper alias of Pair<Statement Number, Variable> to represent an while statement.
     */
    using WHILE_PAIR = std::pair<StmtNum, Variable>;

    /**
     * Wrapper alias of Pair<Statement Number, Statement Number> to represent a Next Relationship.
     */
    using NEXT_PAIR = std::pair<StmtNum, StmtNum>;

    /**
     * Wrapper alias of Pair<Statement Number, Statement Number> to represent a Affect Relationship.
     */
    using AFFECT_PAIR = std::pair<StmtNum, StmtNum>;
};
