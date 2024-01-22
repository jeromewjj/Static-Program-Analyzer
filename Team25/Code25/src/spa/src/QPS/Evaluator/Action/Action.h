
#include <memory>
#include <stack>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Evaluator/DataStructure/Context.h"
#include "QPS/Evaluator/DataStructure/Memo.h"

#ifndef SPA_ACTION_H
#define SPA_ACTION_H

class Action {
protected:
    using ActionStack = std::stack<std::shared_ptr<Action>>;
    Action(const Action& action)
        : reader(action.reader), memo(action.memo), context(action.context), nextActions(action.nextActions){};
    PKBReader& reader;
    Memo& memo;
    Context& context;
    ActionStack& nextActions;

    virtual std::shared_ptr<Action> preTraversalProcess();
    virtual void doAction(){};
    virtual void postTraversalProcess(const std::shared_ptr<Action>& action);

public:
    virtual void execute();

    Action(PKBReader& reader, Memo& memo, Context& context, ActionStack& stack)
        : reader(reader), memo(memo), context(context), nextActions(stack) {}
};

#endif // SPA_ACTION_H
