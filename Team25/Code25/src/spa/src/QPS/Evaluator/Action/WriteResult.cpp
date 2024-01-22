
#include "WriteResult.h"

void WriteResult::doAction() {
    strategy->write(reader, context);
    context.restartEvaluation = true;
}
