#pragma once

#include "QPS/Abstraction/Abstraction.h"
#include "QPS/Constants.h"
#include "QPS/ParserStrategy/RelationStrategy/RelationStrategy.h"
#include "memory"

class RelationStrategyManager {
    std::unique_ptr<RelationStrategy> relationStrategy;

public:
    Abstraction parseAbstraction(std::string rel, std::string ref1, std::string ref2);
    void selectStrategy(std::string rel);
};