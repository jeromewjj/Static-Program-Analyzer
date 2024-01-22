#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include <string>
#include <vector>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Evaluator/Action/ActionStackBuilder.h"
#include "QPS/Query/Query.h"

class Evaluator {
    PKBReader& reader;

public:
    explicit Evaluator(PKBReader& r) : reader(r){};
    std::vector<std::string> evaluateQuery(const Query& query);
};

#endif // SPA_EVALUATOR_H
