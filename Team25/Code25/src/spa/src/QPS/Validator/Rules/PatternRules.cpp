
#include "PatternRules.h"

EntityRules PatternRules::assignEntities = {{EntityType::VARIABLE}};

EntityRules PatternRules::ifEntities = {{EntityType::VARIABLE}};

EntityRules PatternRules::whileEntities = {{EntityType::VARIABLE}};

std::unordered_map<EntityType, EntityRules> PatternRules::RULES = {
    {EntityType::ASSIGN, assignEntities},
    {EntityType::IF, ifEntities},
    {EntityType::WHILE, whileEntities},
};