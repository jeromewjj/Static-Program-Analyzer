#include <utility>

#include "Action.h"
#include "QPS/Abstraction/Abstraction.h"
#include "Strategy/ClauseStrategy.h"

#ifndef SPA_EVALUATECLAUSE_H
#define SPA_EVALUATECLAUSE_H

class EvaluateClause : public Action {
    std::shared_ptr<ClauseStrategy> strategy;

public:
    void doAction() override;
    EvaluateClause(Action& action, std::shared_ptr<ClauseStrategy> strategy)
        : Action(action), strategy(std::move(strategy)){};
};

#endif // SPA_EVALUATECLAUSE_H
