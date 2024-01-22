#pragma once
#include <vector>

#include "AttrCompare.h"
#include "QPS/Clause/CondClause.h"
#include "QPS/Constants.h"
#include "QPS/Parser/ParserUtil.h"
#include "QPS/QPSException/SyntacticException.h"
#include "QPS/QPSGrammarUtil.h"

struct WithClause : CondClause {
    std::unique_ptr<AttrCompare> attrCompare;

public:
    explicit WithClause(std::string attrCond);
    std::vector<std::string> getSynonyms() override;
    std::shared_ptr<ClauseStrategy> getStrat() override;
    void visit(Rulebook& rulebook) override;
};