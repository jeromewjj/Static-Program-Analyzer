#pragma once

#include <string>

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Mappings/BiMapOneToOne.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "PKB/Utils/StarRelationshipUtil.h"
#include "QPS/Argument/Argument.h"

#ifndef SPA_NEXTSTORE_H
#define SPA_NEXTSTORE_H

class NextStore {
public:
    using NextSet = std::unordered_set<RelationshipTypes::NEXT_PAIR>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;

    /**
     * Sets a set of Next relationship between a set of statements into the storage.
     *
     * @param nextSet - The set of statements that have a Next relation amongst each other.
     */
    void setNextRelationships(const NextSet& nextSet);

    /**
     * Get a set of next stmt
     *
     * @param stmtNum - represent the statement number of the Previous in spotlight.
     * @return set of next stmt
     */
    StmtSet getNext(const StmtNum stmtNum);

    /**
     * Tells if a statement-statement pair has a next relation between them.
     *
     * @param firstArg - represent the statement number of the Previous in spotlight.
     * @param secondArg - represent the statement number of the Next in spotlight.
     * @return bool - the boolean answer.
     */
    bool containNextRelation(Argument firstArg, Argument secondArg);

    /**
     * Tells if a statement-statement pair has a next star relation between them.
     *
     * @param firstArg - represent the statement number of the Previous in spotlight.
     * @param secondArg - represent the statement number of the Next in spotlight.
     * @return bool - the boolean answer.
     */
    bool containNextStarRelation(Argument firstArg, Argument secondArg);

    /**
     * Generate the transitive relationship of Next
     */
    void generateNextStarRelationship();

    /**
     * Cleat Next Star Store (to be used after each query)
     */
    void clearNextStarStore();

private:
    BiMapManyToMany<StmtNum, StmtNum> nextStore;
    BiMapManyToMany<StmtNum, StmtNum> nextStarStore;
    NextSet nextPairSet;
    bool isStarGenerated = false;
};

#endif // SPA_NEXTSTORE_H
