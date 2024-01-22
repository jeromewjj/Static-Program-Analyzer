#pragma once

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "QPS/Argument/Argument.h"

/**
 * @class WhileStatementStore
 * Class to represent the while statements.
 */
class WhileStatementStore {
public:
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using WhileSet = std::unordered_set<RelationshipTypes::WHILE_PAIR>;

    /**
     * Sets the given while statements into the while storage.
     *
     */
    void setWhileStatements(const WhileSet& whileSet);

    /**
     * Tells if there is a statement number to a variable mapping in the while storage.
     * @param stmtNum - statement number in spotlight.
     * @param variable - variable in spotlight.
     * @return bool
     */
    bool containsWhilePattern(StmtNum stmtNum, Argument firstArg);

private:
    BiMapManyToMany<EntityTypes::STATEMENT_NUMBER, EntityTypes::VARIABLE> whileStore;
};