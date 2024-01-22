#ifndef SPA_CONTEXT_H
#define SPA_CONTEXT_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "QPS/Evaluator/Entity/Entity.h"

struct Context {
    // mapping from synonym to current pos in typeToEntityMap
    std::unordered_map<std::string, Entity> synonymPos;
    // store results
    std::unordered_set<std::string> result;
    // allow reevaluation of the values
    bool restartEvaluation;
    Context() : synonymPos(), result(), restartEvaluation(false){};
};
#endif // SPA_CONTEXT_H
