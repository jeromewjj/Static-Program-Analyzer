#import <unordered_map>
#import <unordered_set>

#import "QPS/Abstraction/Abstraction.h"
#import "QPS/Evaluator/Entity/Entity.h"

#ifndef ABSTRACTION_RULES_H
#define ABSTRACTION_RULES_H

using EntityRules = std::vector<std::unordered_set<EntityType>>;

namespace AbstractionRules {

    extern EntityRules followsEntities;

    extern EntityRules parentsEntities;

    extern EntityRules modifiesEntities;

    extern EntityRules usesEntities;

    extern EntityRules callsEntities;

    extern EntityRules nextEntities;

    extern EntityRules affectEntities;

    std::unordered_map<AbstractionType, EntityRules>
    expandStatementSubTypes(const std::unordered_map<AbstractionType, EntityRules>& rules);

    extern std::unordered_map<AbstractionType, EntityRules> RULES;
};

#endif
