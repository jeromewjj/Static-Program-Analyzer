#include "CondClause.h"

std::shared_ptr<ClauseStrategy> CondClause::setNotStrategy(std::shared_ptr<ClauseStrategy> strategy) const {
    if (isNot) {
        return std::make_shared<NotStrategy>(strategy);
    }
    return strategy;
}

std::shared_ptr<ClauseStrategy> CondClause::getStrategy() {
    return setNotStrategy(getStrat());
}
