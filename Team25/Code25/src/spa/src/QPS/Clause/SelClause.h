#include <memory>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Declaration/Declaration.h"
#include "QPS/Evaluator/Action/Strategy/ResultStrategy.h"

#ifndef SPA_SELCLAUSE_H
#define SPA_SELCLAUSE_H

struct SelClause {
    std::shared_ptr<Argument> argument;

public:
    explicit SelClause(std::shared_ptr<Argument> argument) : argument(std::move(argument)){};
    [[nodiscard]] std::shared_ptr<ResultStrategy> getStrategy() const;
};

#endif // SPA_SELCLAUSE_H
