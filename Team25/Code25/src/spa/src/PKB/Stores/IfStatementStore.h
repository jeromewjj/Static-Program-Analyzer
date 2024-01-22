#pragma once

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "QPS/Argument/Argument.h"

/**
 * @class IfStatementStore
 * Class to represent the if statements.
 */
class IfStatementStore {
public:
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using IfSet = std::unordered_set<RelationshipTypes::If_PAIR>;

    /**
     * Sets the given if statements into the if storage.
     *
     */
    void setIfStatements(const IfSet& ifSet);

    /**
     * Tells if there is a statement number to a variable mapping in the if storage.
     * @param stmtNum - statement number in spotlight.
     * @param variable - variable in spotlight.
     * @return bool
     */
    bool containsIfPattern(StmtNum stmtNum, Argument firstArg);

private:
    BiMapManyToMany<EntityTypes::STATEMENT_NUMBER, EntityTypes::VARIABLE> ifStore;
};