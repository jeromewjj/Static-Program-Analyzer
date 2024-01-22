
#include "StartEvaluation.h"

void StartEvaluation::doAction() {
    if (!strategy->tryShortCircuit(reader, context)) {
        nextActions.top()->execute();
    }
    context.restartEvaluation = false;
}
