#include <utility>

#pragma once

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Argument/Argument.h"
#include "QPS/Evaluator/DataStructure/Context.h"
#include "QPS/Evaluator/PKBReaderHandler/AttributeHandler.h"
#include "QPS/Evaluator/Util.h"

class ResultStrategy {
public:
    virtual bool tryShortCircuit(const PKBReader& reader, Context& context);
    virtual void write(const PKBReader& reader, Context& context){};
    virtual void defaultWrite(Context& context){};
};

class SingleResult : public ResultStrategy {
    Argument argument;

public:
    void write(const PKBReader& reader, Context& context) override;
    bool tryShortCircuit(const PKBReader& reader, Context& context);
    explicit SingleResult(Argument argument_) : argument(std::move(argument_)){};
};

class BooleanResult : public ResultStrategy {
public:
    void write(const PKBReader& reader, Context& context) override;
    void defaultWrite(Context& context) override;
};

class TupleResult : public ResultStrategy {
    std::vector<Argument> arguments;

public:
    void write(const PKBReader& reader, Context& context) override;
    bool tryShortCircuit(const PKBReader& reader, Context& context);
    explicit TupleResult(std::vector<Argument> arguments_) : arguments(std::move(arguments_)){};
};
