#include "QPS.h"

#include <string>

Query QPS::parseQuery(std::string& queryInput) {
    return parser->parseQuery(queryInput);
}

std::vector<std::string> QPS::evaluateQuery(Query query) {
    return evaluator->evaluateQuery(query);
}

std::vector<std::string> QPS::processQuery(std::string queryInput) {
    std::vector<std::string> res;
    try {
        auto query = parseQuery(queryInput);
        validator->validateQuery(query);
        res = evaluateQuery(query);
    } catch (SpaException& e) {
        std::string errorMessage(e.what());
        res.push_back(errorMessage);
    }
    return res;
}