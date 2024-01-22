#include "WriteResult.h"

#ifndef SPA_CLEANRESULT_H
#define SPA_CLEANRESULT_H

class CleanResult : public Action {
    std::shared_ptr<ResultStrategy> strategy;

public:
    CleanResult(Action& action, std::shared_ptr<ResultStrategy> strategy_)
        : Action(action), strategy(std::move(strategy_)) {}
    void doAction() override;
};

#endif // SPA_CLEANRESULT_H
