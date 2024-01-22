#pragma once

#include <string>

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Mappings/BiMapOneToOne.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "PKB/Utils/StarRelationshipUtil.h"
#include "QPS/Argument/Argument.h"

class FollowsStore {
public:
    using FollowsSet = std::unordered_set<RelationshipTypes::FOLLOWS_PAIR>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;

    /**
     * Sets a follows relationship between a set of statements into the storage.
     *
     * @param followSet - The set of statements that have a follows relation amongst each other.
     */

    void setFollowsRelationships(const FollowsSet& followSet);

    /**
     * Gets the statement number representing the statement that follows a given statement.
     *
     * @param followee - the statement number of the statement in spotlight.
     * @return the statement number of the following statement.
     */

    StmtNum getFollower(StmtNum followee);

    /**
     * Gets the list of statement numbers representing the statements that follows a given statement directly ot
     * indirectly.
     *
     * @param followee - the statement number of the statement in spotlight.
     * @return the set of statement numbers of the following statements.
     */

    StmtSet getFollowerStars(StmtNum followee);

    /**
     * Gets the statement number of the statement whom a given statement follows.
     *
     * @param follower - the statement number of the statement in spotlight.
     * @return the statement number of the statement followed by the given statement.
     */

    StmtNum getFollowee(StmtNum follower);

    /**
     * Gets the list of statement numbers whom a given statement follows.
     *
     * @param follower - the statement number of the statement in spotlight.
     * @return the set of statement numbers of the statements followed by the given statement.
     */

    StmtSet getFolloweeStars(StmtNum follower);

    /**
     * Tells if a statement-statement pair has a follows relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containFollowsRelation(StmtNum followee, StmtNum follower);

    /**
     * Tells if a statement-statement pair has a follows star relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containFollowsStarRelation(StmtNum followee, StmtNum follower);

    /**
     * Tells if a statement-statement pair has a follows relation between them.
     *
     * @param firstArg - represent the statement number of the followee in spotlight.
     * @param secondArg - represent the statement number of the follower in spotlight.
     * @return bool - the boolean answer.
     */
    bool containFollowsRelation(Argument firstArg, Argument secondArg);

    /**
     * Tells if a statement-statement pair has a follows star relation between them.
     *
     * @param firstArg - represent the statement number of the followee in spotlight.
     * @param secondArg - represent the statement number of the follower in spotlight.
     * @return
     */
    bool containFollowsStarRelation(Argument firstArg, Argument secondArg);

private:
    BiMapOneToOne<StmtNum, StmtNum> followsStore;
    BiMapManyToMany<StmtNum, StmtNum> followsStarStore;
};
