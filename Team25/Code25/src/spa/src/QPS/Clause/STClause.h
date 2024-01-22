//
// Created by User on 18/9/2023.
//

#ifndef SPA_STCLAUSE_H
#define SPA_STCLAUSE_H

#include <string>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Abstraction/Abstraction.h"
#include "QPS/Clause/CondClause.h"
#include "QPS/Declaration/Declaration.h"
#include "QPS/Evaluator/DataStructure/Context.h"

struct STClause : public CondClause {
    Abstraction abstraction;

public:
    STClause();
    explicit STClause(Abstraction& abstraction, bool isNot) : abstraction(abstraction) {
        this->isNot = isNot;
    };
    std::vector<std::string> getSynonyms() override;
    std::shared_ptr<ClauseStrategy> getStrat() override;
    void visit(Rulebook& rulebook) override;
};

#endif // SPA_STCLAUSE_H