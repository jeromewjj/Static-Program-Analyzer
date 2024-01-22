#include <utility>

#include "Action.h"
#include "Strategy/ResultStrategy.h"

#ifndef SPA_WRITERESULT_H
#define SPA_WRITERESULT_H

class WriteResult : public Action {
    std::shared_ptr<ResultStrategy> strategy;

public:
    WriteResult(Action& action, std::shared_ptr<ResultStrategy> strategy_)
        : Action(action), strategy(std::move(strategy_)) {}
    void doAction() override;
};

#endif // SPA_WRITERESULT_H
