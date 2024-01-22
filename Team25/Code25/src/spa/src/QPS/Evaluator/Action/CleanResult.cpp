

#include "CleanResult.h"

void CleanResult::doAction() {
    nextActions.top()->execute();
    if (context.result.empty()) {
        strategy->defaultWrite(context);
    }
}
