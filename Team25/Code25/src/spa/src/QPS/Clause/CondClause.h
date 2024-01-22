#ifndef SPA_CONDCLAUSE_H
#define SPA_CONDCLAUSE_H
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Abstraction/Abstraction.h"
#include "QPS/Evaluator/Action/EvaluateClause.h"
#include "QPS/Evaluator/DataStructure/Context.h"
#include "QPS/Evaluator/Entity/Entity.h"
#include "QPS/Validator/Rulebook.h"

class CondClause {
protected:
    [[nodiscard]] std::shared_ptr<ClauseStrategy> setNotStrategy(std::shared_ptr<ClauseStrategy> strategy) const;
    virtual std::shared_ptr<ClauseStrategy> getStrat(){};

public:
    bool isNot;

    CondClause(){};
    virtual ~CondClause(){};
    virtual std::vector<std::string> getSynonyms(){};
    virtual std::shared_ptr<ClauseStrategy> getStrategy();
    virtual void visit(Rulebook& rulebook){};
};

#endif // SPA_CONDCLAUSE_H
