#include "Action.h"
#include "CleanResult.h"
#include "EvaluateClause.h"
#include "IterateSynonym.h"
#include "StartEvaluation.h"
#include "Strategy/ResultStrategy.h"
#include "WriteResult.h"

#ifndef SPA_ACTIONFACTORY_H
#define SPA_ACTIONFACTORY_H

class ActionFactory {
    Action actionTemplate;
    using ActionStack = std::stack<std::shared_ptr<Action>>;

public:
    ActionFactory(PKBReader& reader, Memo& memo, Context& context, ActionStack& stack)
        : actionTemplate(reader, memo, context, stack){};
    std::shared_ptr<Action> createWriteResult(const std::shared_ptr<ResultStrategy>& writeStrategy);
    std::shared_ptr<Action> createIterateSynonym(std::string synonym);
    std::shared_ptr<Action> createStartEvaluation(const std::shared_ptr<ResultStrategy>& writeStrategy);
    std::shared_ptr<Action> createEvaluateClause(const std::shared_ptr<ClauseStrategy>& strategy);
    std::shared_ptr<Action> createCleanResult(const std::shared_ptr<ResultStrategy>& writeStrategy);
};

#endif // SPA_ACTIONFACTORY_H
