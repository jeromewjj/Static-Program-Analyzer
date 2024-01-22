
#include <memory>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Declaration/Declaration.h"
#include "QPS/Evaluator/Entity/Entity.h"

#ifndef SPA_MEMO_H
#define SPA_MEMO_H

struct Memo {
    // mapping from synonym to entity type
    std::unordered_map<std::string, EntityType> synonymToEntityMap;
    // mapping from entity type to a vector of entities
    std::unordered_map<EntityType, std::vector<Entity>> typeToEntityMap;
    // create shared ptr to Memo
    static Memo createMemo(PKBReader& reader, const std::vector<Declaration>& declarations);
};

#endif // SPA_MEMO_H
