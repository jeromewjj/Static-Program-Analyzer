
#include "ActionFactory.h"

#include "Strategy/ResultStrategy.h"

std::shared_ptr<Action> ActionFactory::createWriteResult(const std::shared_ptr<ResultStrategy>& writeStrategy) {
    return std::make_shared<WriteResult>(actionTemplate, writeStrategy);
}

std::shared_ptr<Action> ActionFactory::createIterateSynonym(std::string synonym) {
    return std::make_shared<IterateSynonym>(actionTemplate, std::move(synonym));
}

std::shared_ptr<Action> ActionFactory::createStartEvaluation(const std::shared_ptr<ResultStrategy>& strategy) {
    return std::make_shared<StartEvaluation>(actionTemplate, strategy);
}

std::shared_ptr<Action> ActionFactory::createEvaluateClause(const std::shared_ptr<ClauseStrategy>& strategy) {
    return std::make_shared<EvaluateClause>(actionTemplate, strategy);
}

std::shared_ptr<Action> ActionFactory::createCleanResult(const std::shared_ptr<ResultStrategy>& writeStrategy) {
    return std::make_shared<CleanResult>(actionTemplate, writeStrategy);
}
