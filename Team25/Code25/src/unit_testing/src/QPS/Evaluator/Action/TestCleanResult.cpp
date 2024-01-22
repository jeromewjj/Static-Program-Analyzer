#include "../../Mocks.h"
#include "QPS/Evaluator/Action/CleanResult.h"
#include "catch.hpp"

TEST_CASE("Test CleanResult") {
    PKB pkb;
    Mock::MockPKBReader reader(pkb);
    Context context;
    Memo memo;
    std::stack<std::shared_ptr<Action>> stack;

    Action templateAction{reader, memo, context, stack};

    {
        auto emptyAction = std::make_shared<Action>(reader, memo, context, stack);
        auto strategy = std::make_shared<Mock::MockResultStrategy>();
        auto action = std::make_shared<CleanResult>(templateAction, strategy);
        stack.push(emptyAction);

        action->doAction();
        REQUIRE(context.result.count("MOCKED") == 1);
    }
}