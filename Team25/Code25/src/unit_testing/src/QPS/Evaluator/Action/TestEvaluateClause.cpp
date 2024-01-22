#include "../../Mocks.h"
#include "QPS/Evaluator/Action/EvaluateClause.h"
#include "catch.hpp"

TEST_CASE("Test EvaluateClause") {
    PKB pkb;
    Mock::MockPKBReader reader(pkb);
    Context context;
    Memo memo;
    std::stack<std::shared_ptr<Action>> stack;

    Action templateAction{reader, memo, context, stack};

    {
        auto counter = std::make_shared<Mock::CounterAction>(templateAction);
        auto strategy = std::make_shared<Mock::MockTrueStrategy>();
        EvaluateClause action(templateAction, strategy);
        stack.push(counter);

        action.doAction();
        REQUIRE_FALSE(context.result.empty());
        context.result.clear();
        stack.pop();
    }

    {
        auto counter = std::make_shared<Mock::CounterAction>(templateAction);
        auto strategy = std::make_shared<Mock::MockFalseStrategy>();
        EvaluateClause action(templateAction, strategy);
        stack.push(counter);

        action.doAction();
        REQUIRE(context.result.empty());
        context.result.clear();
        stack.pop();
    }
}