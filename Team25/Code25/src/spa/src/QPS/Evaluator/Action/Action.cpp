
#include "Action.h"

#include "WriteResult.h"

void Action::execute() {
    auto action = preTraversalProcess();
    doAction();
    postTraversalProcess(action);
}

std::shared_ptr<Action> Action::preTraversalProcess() {
    // pop action from nextAction
    auto action = nextActions.top();
    nextActions.pop();
    return action;
}

void Action::postTraversalProcess(const std::shared_ptr<Action>& action) {
    // push action into nextAction
    nextActions.push(action);
}
