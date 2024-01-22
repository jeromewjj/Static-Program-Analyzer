#pragma once

#include <vector>

#include "QPS/Argument/Argument.h"
#include "string"

class RelationStrategy {
public:
    virtual ~RelationStrategy() = default;
    virtual std::vector<Argument> parseArgs(std::string ref1, std::string ref2) = 0;
};