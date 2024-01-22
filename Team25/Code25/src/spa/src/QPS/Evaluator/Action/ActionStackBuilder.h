#include <memory>
#include <stack>

#include "Action.h"

#ifndef SPA_ACTIONSTACKBUILDER_H
#define SPA_ACTIONSTACKBUILDER_H

#include "ActionFactory.h"
#include "QPS/Query/Query.h"

class ActionStackBuilder {
    const Query& query;
    Context& context;
    Memo& memo;
    PKBReader& reader;

public:
    std::stack<std::shared_ptr<Action>> buildStack();
    ActionStackBuilder(const Query& query, Context& context, Memo& memo, PKBReader& reader)
        : query(query), context(context), memo(memo), reader(reader){};
};

#endif // SPA_ACTIONSTACKBUILDER_H
