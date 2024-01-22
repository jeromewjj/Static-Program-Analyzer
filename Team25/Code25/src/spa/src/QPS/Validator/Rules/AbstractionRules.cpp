
#include "AbstractionRules.h"

const EntityType STATEMENT_SUBTYPES[] = {EntityType::ASSIGN, EntityType::CALL, EntityType::WHILE,
                                         EntityType::IF,     EntityType::READ, EntityType::PRINT};

EntityRules AbstractionRules::followsEntities = {{EntityType::STATEMENT}, {EntityType::STATEMENT}};

EntityRules AbstractionRules::parentsEntities = {{EntityType::STATEMENT}, {EntityType::STATEMENT}};

EntityRules AbstractionRules::modifiesEntities = {{EntityType::STATEMENT, EntityType::PROCEDURE},
                                                  {EntityType::VARIABLE}};

EntityRules AbstractionRules::usesEntities = {{EntityType::STATEMENT, EntityType::PROCEDURE}, {EntityType::VARIABLE}};

EntityRules AbstractionRules::callsEntities = {{EntityType::PROCEDURE}, {EntityType::PROCEDURE}};

EntityRules AbstractionRules::nextEntities = {{EntityType::STATEMENT}, {EntityType::STATEMENT}};

EntityRules AbstractionRules::affectEntities = {{EntityType::STATEMENT}, {EntityType::STATEMENT}};

std::unordered_map<AbstractionType, EntityRules>
AbstractionRules::expandStatementSubTypes(const std::unordered_map<AbstractionType, EntityRules>& rules) {
    std::unordered_map<AbstractionType, EntityRules> newRules;
    for (const auto& [key, value] : rules) {
        EntityRules rule;
        for (const auto& setType : value) {
            std::unordered_set<EntityType> types;
            for (const auto& type : setType) {
                types.insert(type);
                if (type == EntityType::STATEMENT) {
                    for (const auto& subtype : STATEMENT_SUBTYPES) {
                        types.insert(subtype);
                    }
                }
            }
            rule.push_back(types);
        }
        newRules[key] = rule;
    }
    return newRules;
}

namespace AbstractionRules {
    std::unordered_map<AbstractionType, EntityRules> RULES = expandStatementSubTypes({
        {AbstractionType::FOLLOWS, followsEntities},
        {AbstractionType::FOLLOWS_T, followsEntities},
        {AbstractionType::PARENTS, parentsEntities},
        {AbstractionType::PARENTS_T, parentsEntities},
        {AbstractionType::CALLS, callsEntities},
        {AbstractionType::CALLS_T, callsEntities},
        {AbstractionType::NEXT, nextEntities},
        {AbstractionType::NEXT_T, nextEntities},
        {AbstractionType::MODIFIES, modifiesEntities},
        {AbstractionType::USES, usesEntities},
        {AbstractionType::AFFECTS, affectEntities},
    });
}
