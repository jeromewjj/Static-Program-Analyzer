#include "Evaluator.h"

#include "QPS/Clause/SelClause.h"

std::vector<std::string> Evaluator::evaluateQuery(const Query& query) {
    // initialize context, memo, ActionStackBuilder
    Context context;
    Memo memo = Memo::createMemo(reader, query.declarations);
    ActionStackBuilder stackBuilder{query, context, memo, reader};

    // build ActionStack
    auto actionStack = stackBuilder.buildStack();

    // traverse ActionStack
    actionStack.top()->execute();

    // write result
    std::vector<std::string> result;
    result.reserve(context.result.size());
    for (const auto& s : context.result) {
        result.push_back(s);
    }

    return result;
}