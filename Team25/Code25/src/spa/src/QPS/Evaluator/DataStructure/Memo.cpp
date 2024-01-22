
#include "Memo.h"

#include "QPS/Evaluator/PKBReaderHandler/EntityHandler.h"

Memo Memo::createMemo(PKBReader& reader, const std::vector<Declaration>& declarations) {
    Memo memo;
    for (const auto& declaration : declarations) {
        memo.synonymToEntityMap[declaration.synonym] = declaration.entityType;
        if (memo.typeToEntityMap.count(declaration.entityType) == 0) {
            auto v = PKBEntity::HANDLERS.at(declaration.entityType)(reader);
            memo.typeToEntityMap[declaration.entityType] = v;
        }
    }
    return memo;
}
