#import <unordered_map>
#import <unordered_set>

#import "QPS/Evaluator/Entity/Entity.h"

#ifndef SPA_PATTERNRULES_H
#define SPA_PATTERNRULES_H

using EntityRules = std::vector<std::unordered_set<EntityType>>;

namespace PatternRules {

    extern EntityRules assignEntities;

    extern EntityRules ifEntities;

    extern EntityRules whileEntities;

    extern std::unordered_map<EntityType, EntityRules> RULES;
};

#endif // SPA_PATTERNRULES_H
