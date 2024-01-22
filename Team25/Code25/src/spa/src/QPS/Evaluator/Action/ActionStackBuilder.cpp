
#include "ActionStackBuilder.h"

std::stack<std::shared_ptr<Action>> ActionStackBuilder::buildStack() {
    std::stack<std::shared_ptr<Action>> stack;
    ActionFactory factory{reader, memo, context, stack};
    std::vector<std::shared_ptr<Action>> temp;
    std::unordered_set<std::string> initialized_synonyms;

    // select clause type
    const auto& strategy = query.selClause.getStrategy();
    auto writeResult = factory.createWriteResult(strategy);
    stack.push(writeResult);

    // run through sel clause first
    if (query.selClause.argument->type == ArgType::TUPLE) {
        for (const auto& str : query.selClause.argument->getSynonyms()) {
            temp.push_back(factory.createIterateSynonym(str));
            initialized_synonyms.insert(str);
        }
    }

    temp.push_back(factory.createStartEvaluation(strategy));

    // run through the rest of cond clause
    for (const auto& clause : query.clauses) {
        const auto& synonyms = clause->getSynonyms();
        for (const auto& s : synonyms) {
            if (initialized_synonyms.count(s) == 0) {
                temp.push_back(factory.createIterateSynonym(s));
                initialized_synonyms.insert(s);
            }
        }
        temp.push_back(factory.createEvaluateClause(clause->getStrategy()));
    }

    // populate stack
    for (size_t i = temp.size() - 1; i > 0; i--) {
        stack.push(temp[i]);
    }
    stack.push(temp[0]);

    // add a cleanup action
    stack.push(factory.createCleanResult(strategy));

    return stack;
}
