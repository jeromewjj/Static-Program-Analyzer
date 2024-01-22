#pragma once

#include <string>

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Mappings/BiMapOneToOne.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "PKB/Utils/StarRelationshipUtil.h"
#include "QPS/Argument/Argument.h"

#ifndef SPA_AFFECTSTORE_H
#define SPA_AFFECTSTORE_H

class AffectStore {
public:
    using AffectSet = std::unordered_set<RelationshipTypes::AFFECT_PAIR>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;

    /**
     * Sets a set of Affect relationship between a set of statements into the storage.
     *
     * @param affectSet - The set of statements that have a affect relation amongst each other.
     */
    void setAffectRelationships(const AffectSet& affectSet);

    /**
     * Tells if a statement-statement pair has a next relation between them.
     *
     * @param firstArg - represent the statement number of the Previous in spotlight.
     * @param secondArg - represent the statement number of the Next in spotlight.
     * @return bool - the boolean answer.
     */
    bool containAffectRelation(Argument firstArg, Argument secondArg);

    /**
     * Cleat Affect Store (to be used after each query)
     */
    void clearAffectStore();

    /**
     * Check if affect relationship is generated
     *
     * @return bool - the boolean answer.
     */
    bool checkAffectGenerated();

private:
    BiMapManyToMany<StmtNum, StmtNum> affectStore;
    bool isAffectGenerated = false;
};

#endif // SPA_AFFECTSTORE_H
