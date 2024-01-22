#include "RelationStrategyManager.h"

#include "QPS/ParserStrategy/RelationStrategy/AffectsStrategy.h"
#include "QPS/ParserStrategy/RelationStrategy/CallsStrategy.h"
#include "QPS/ParserStrategy/RelationStrategy/FollowsStrategy.h"
#include "QPS/ParserStrategy/RelationStrategy/ModifiesStrategy.h"
#include "QPS/ParserStrategy/RelationStrategy/NextStrategy.h"
#include "QPS/ParserStrategy/RelationStrategy/ParentStrategy.h"
#include "QPS/ParserStrategy/RelationStrategy/UsesStrategy.h"

Abstraction RelationStrategyManager::parseAbstraction(std::string rel, std::string ref1, std::string ref2) {
    selectStrategy(rel);

    std::vector<Argument> argList = relationStrategy->parseArgs(ref1, ref2);

    if (rel == Constants::FOLLOWS_PATTERN) {
        return {AbstractionType::FOLLOWS, argList};
    }
    else if (rel == Constants::FOLLOWST_PATTERN) {
        return {AbstractionType::FOLLOWS_T, argList};
    }
    else if (rel == Constants::PARENT_PATTERN) {
        return {AbstractionType::PARENTS, argList};
    }
    else if (rel == Constants::PARENTT_PATTERN) {
        return {AbstractionType::PARENTS_T, argList};
    }
    else if (rel == Constants::MODIFIES_PATTERN) {
        return {AbstractionType::MODIFIES, argList};
    }
    else if (rel == Constants::USES_PATTERN) {
        return {AbstractionType::USES, argList};
    }
    else if (rel == Constants::CALLS_PATTERN) {
        return {AbstractionType::CALLS, argList};
    }
    else if (rel == Constants::CALLST_PATTERN) {
        return {AbstractionType::CALLS_T, argList};
    }
    else if (rel == Constants::NEXT_PATTERN) {
        return {AbstractionType::NEXT, argList};
    }
    else if (rel == Constants::NEXTT_PATTERN) {
        return {AbstractionType::NEXT_T, argList};
    }
    else if (rel == Constants::AFFECTS_PATTERN) {
        return {AbstractionType::AFFECTS, argList};
    }

    throw std::runtime_error("Invalid relRef: " + rel);
}

void RelationStrategyManager::selectStrategy(std::string rel) {
    if (rel == Constants::FOLLOWS_PATTERN || rel == Constants::FOLLOWST_PATTERN) {
        relationStrategy = std::make_unique<FollowsStrategy>();
    }
    else if (rel == Constants::PARENT_PATTERN || rel == Constants::PARENTT_PATTERN) {
        relationStrategy = std::make_unique<ParentStrategy>();
    }
    else if (rel == Constants::MODIFIES_PATTERN) {
        relationStrategy = std::make_unique<ModifiesStrategy>();
    }
    else if (rel == Constants::USES_PATTERN) {
        relationStrategy = std::make_unique<UsesStrategy>();
    }
    else if (rel == Constants::CALLS_PATTERN || rel == Constants::CALLST_PATTERN) {
        relationStrategy = std::make_unique<CallsStrategy>();
    }
    else if (rel == Constants::NEXT_PATTERN || rel == Constants::NEXTT_PATTERN) {
        relationStrategy = std::make_unique<NextStrategy>();
    }
    else if (rel == Constants::AFFECTS_PATTERN) {
        relationStrategy = std::make_unique<AffectsStrategy>();
    }
    else {
        throw std::runtime_error("Invalid relRef: " + rel);
    }
}