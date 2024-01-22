#pragma once

#include <unordered_set>

#include "PKB/Mappings//BiMapOneToMany.h"
#include "PKB/Mappings//BiMapOneToOne.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/StatementType.h"

class StatementStore {
public:
    using StatementSet = std::unordered_set<EntityTypes::STATEMENT>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;

    /**
     * Sets a set of statements into the statement store.
     *
     * @param statements - The set of statements to be stored.
     */

    void setStatements(const StatementSet& statements);

    /**
     * Gets the type of the statement represented by its statament number.
     *
     * @param stmtNum - the statement number representing the statement in spotlight.
     * @return StatementType - the type of the statement in spotlight
     */

    StatementType getStmtType(StmtNum stmtNum);

    /**
     * Gets the set of statement numbers representing the statements belonging to a particular type.
     *
     * @param type - the statement type in spotlight.
     * @return StmtSet - the set of statement numbers representing the statements belonging to a particular type.
     */
    StmtSet getStmtNum(StatementType type);

    /**
     * Gets the list of all statement numbers.
     *
     * @return StmtSet - List of all statement numbers.
     */

    StmtSet getAllStmtNum();

private:
    BiMapOneToMany<StatementType, StmtNum> stmtTypeStore;
};