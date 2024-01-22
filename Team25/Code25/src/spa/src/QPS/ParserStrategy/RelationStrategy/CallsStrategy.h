#pragma once

#include "QPS/QPSGrammarUtil.h"
#include "RelationStrategy.h"

class CallsStrategy : public RelationStrategy {
public:
    std::vector<Argument> parseArgs(std::string ref1, std::string ref2) override;
};
