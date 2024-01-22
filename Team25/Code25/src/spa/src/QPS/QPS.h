#pragma once

#include <memory>
#include <string>
#include <vector>

#include "QPS/Evaluator/Evaluator.h"
#include "QPS/Parser/QpsParser.h"
#include "QPS/Query/Query.h"
#include "QPS/Validator/Validator.h"

class QPS {
public:
    explicit QPS(PKBReader& reader)
        : parser(std::make_shared<QpsParser>()), evaluator(std::make_shared<Evaluator>(Evaluator(reader))),
          validator(std::make_shared<Validator>()){};
    Query parseQuery(std::string& queryInput);
    std::vector<std::string> evaluateQuery(Query query);
    // NOTE: queryInput moved
    std::vector<std::string> processQuery(std::string queryInput);

private:
    std::shared_ptr<Validator> validator;
    std::shared_ptr<QpsParser> parser;
    std::shared_ptr<Evaluator> evaluator;
};
