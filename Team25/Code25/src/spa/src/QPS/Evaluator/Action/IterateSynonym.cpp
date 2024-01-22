
#include "IterateSynonym.h"

void IterateSynonym::doAction() {
    auto type = memo.synonymToEntityMap[synonym];
    auto& entities = memo.typeToEntityMap[type];

    for (const auto& e : entities) {
        context.synonymPos[synonym] = e;

        nextActions.top()->execute();

        if (context.restartEvaluation) {
            break;
        }
    }
    context.synonymPos.erase(synonym);
}
