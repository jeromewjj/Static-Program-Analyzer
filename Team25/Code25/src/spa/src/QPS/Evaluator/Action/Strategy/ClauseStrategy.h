#include <utility>

#include "../Action.h"
#include "QPS/Abstraction/Abstraction.h"

#ifndef SPA_CLAUSESTRATEGY_H
#define SPA_CLAUSESTRATEGY_H

class ClauseStrategy {
public:
    virtual bool execute(const PKBReader& reader, const Context& context) {
        return false;
    };
};

class STStrategy : public ClauseStrategy {
    Abstraction abstraction;

public:
    bool execute(const PKBReader& reader, const Context& context) override;
    explicit STStrategy(Abstraction abstraction1) : abstraction(std::move(abstraction1)){};
};

class PatStrategy : public ClauseStrategy {
    std::string patternSynonym;
    std::vector<Argument> args;

public:
    bool execute(const PKBReader& reader, const Context& context) override;
    PatStrategy(std::string patSyn, std::vector<Argument> args)
        : patternSynonym(std::move(patSyn)), args(std::move(args)){};
};

class WithStrategy : public ClauseStrategy {
    Argument leftArg;
    Argument rightArg;

public:
    bool execute(const PKBReader& reader, const Context& context) override;
    WithStrategy(Argument leftArg, Argument rightArg) : leftArg(std::move(leftArg)), rightArg(std::move(rightArg)){};
};

class NotStrategy : public ClauseStrategy {
    std::shared_ptr<ClauseStrategy> strategy;

public:
    explicit NotStrategy(std::shared_ptr<ClauseStrategy> strategy) : strategy(std::move(strategy)){};
    bool execute(const PKBReader& reader, const Context& context) override;
};

#endif // SPA_CLAUSESTRATEGY_H
