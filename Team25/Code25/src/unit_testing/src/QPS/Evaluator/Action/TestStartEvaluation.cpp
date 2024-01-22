#include "../../Mocks.h"
#include "QPS/Evaluator/Action/StartEvaluation.h"
#include "catch.hpp"

TEST_CASE("Test StartEvaluation") {
    PKB pkb;
    Mock::MockPKBReader reader(pkb);
    Context context;
    Memo memo;
    std::stack<std::shared_ptr<Action>> stack;

    Action templateAction{reader, memo, context, stack};

    {
        StartEvaluation action{templateAction, std::make_shared<ResultStrategy>()};
        auto counter = std::make_shared<Mock::CounterAction>(templateAction);
        stack.push(counter);

        context.restartEvaluation = true;
        action.doAction();
        REQUIRE_FALSE(context.restartEvaluation);
        REQUIRE_FALSE(context.result.empty());
        context.result.clear();
        stack.pop();
    }

    {
        StartEvaluation action{templateAction, std::make_shared<Mock::MockResultStrategy>()};
        auto counter = std::make_shared<Mock::CounterAction>(templateAction);
        stack.push(counter);

        context.restartEvaluation = true;
        action.doAction();
        REQUIRE_FALSE(context.restartEvaluation);
        REQUIRE(context.result.empty());
        context.result.clear();
        stack.pop();
    }
}