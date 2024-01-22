#include "STClause.h"

#include "QPS/Evaluator/DataStructure/Context.h"
#include "QPS/Evaluator/PKBReaderHandler/EntityHandler.h"

std::string removeQuotes(const std::string& input) {
    std::string result = input;

    // Remove all parentheses
    result.erase(std::remove(result.begin(), result.end(), '\''), result.end());
    result.erase(std::remove(result.begin(), result.end(), '\"'), result.end());

    return result;
}

std::vector<std::string> STClause::getSynonyms() {
    std::vector<std::string> temp;
    for (const auto& arg : abstraction.args) {
        if (arg.type == ArgType::SYNONYM) {
            temp.push_back(arg.str);
        }
    }
    return temp;
}

std::shared_ptr<ClauseStrategy> STClause::getStrat() {
    auto strategy = std::make_shared<STStrategy>(abstraction);
    return strategy;
}

void STClause::visit(Rulebook& rulebook) {
    rulebook.testSTClause(abstraction);
}
