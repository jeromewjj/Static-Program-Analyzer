#pragma once

#include "PKB/Mappings//BiMapManyToMany.h"
#include "PKB/Mappings//BiMapOneToMany.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "PKB/Utils/StarRelationshipUtil.h"
#include "QPS/Argument/Argument.h"

class ParentStore {
public:

public:
    using ParentSet = std::unordered_set<RelationshipTypes::PARENT_PAIR>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;

    /**
     * Sets a parent relationship between a set of statements.
     *
     * @param parentSet - The set of statement-statement parent relationship to be stored.
     */

    void setParentRelationship(const ParentSet& parentSet);

    /**
     * Gets the set of statement numbers representing the statements that are the children of the given statement.
     *
     * @param parent - the statement number of the statement in spotlight.
     * @return StmtSet - the set of statement numbers representing the statements that are the children
     * of the given statement.
     */

    StmtSet getChilds(StmtNum parent);

    /**
     * Gets the set of statement numbers representing the statements that are indirect children of the given statement.
     *
     * @param parent - the statement number of the statement in spotlight.
     * @return StmtSet - the set of statement numbers representing the statements that are indirect children
     * of the given statement.
     */

    StmtSet getChildsStar(StmtNum parent);

    /**
     * Gets the statement number representing the statement that is the parent of the given statement.
     *
     * @param child - the statement number of the statement in spotlight.
     * @return StmtNum - the statement number representing the statement that is the parent of the given
     * statement.
     */

    StmtNum getParent(StmtNum child);

    /**
     * Gets the set of statement numbers representing the statements that are indirect parents of the given statement.
     *
     * @param parent - the statement number of the statement in spotlight.
     * @return StmtSet - the set of statement numbers representing the statements that are indirect parents
     * of the given statement.
     */

    StmtSet getParentStar(StmtNum child);

    /**
     * Tells if a statement-statement pair has a parent relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containParentRelation(StmtNum parent, StmtNum child);

    /**
     * Tells if a statement-statement pair has a parent star relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containParentStarRelation(StmtNum parent, StmtNum child);

    /**
     * Tells if a statement-statement pair has a parent relation between them.
     *
     * @param firstArg - represent the statement number of the parent in spotlight.
     * @param secondArg  - represent the statement number of the child in spotlight.
     * @return bool - the boolean answer.
     */
    bool containParentRelation(Argument firstArg, Argument secondArg);

    /**
     * Tells if a statement-statement pair has a parent star relation between them.
     *
     * @param firstArg - represent the statement number of the parent in spotlight.
     * @param secondArg - represent the statement number of the child in spotlight.
     * @return bool - the boolean answer.
     */
    bool containParentStarRelation(Argument firstArg, Argument secondArg);

private:
    BiMapOneToMany<StmtNum, StmtNum> parentStore;
    BiMapManyToMany<StmtNum, StmtNum> parentStarStore;
};
