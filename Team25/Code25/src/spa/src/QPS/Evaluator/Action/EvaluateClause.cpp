
#include "EvaluateClause.h"

void EvaluateClause::doAction() {
    auto res = strategy->execute(reader, context);
    if (res) {
        nextActions.top()->execute();
    }
}
