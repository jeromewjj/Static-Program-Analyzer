#include "Action.h"
#include "Strategy/ResultStrategy.h"

#ifndef SPA_STARTEVALUATION_H
#define SPA_STARTEVALUATION_H

class StartEvaluation : public Action {
    std::shared_ptr<ResultStrategy> strategy;

public:
    StartEvaluation(Action& action, std::shared_ptr<ResultStrategy> strategy_)
        : Action(action), strategy(std::move(strategy_)){};
    void doAction() override;
};

#endif // SPA_STARTEVALUATION_H
