#include "../../Mocks.h"
#include "QPS/Evaluator/Action/IterateSynonym.h"
#include "catch.hpp"

TEST_CASE("Test IterateSynonym") {
    PKB pkb;
    Mock::MockPKBReader reader(pkb);
    Context context;
    Memo memo = Memo::createMemo(reader, Mock::Declarations());
    std::stack<std::shared_ptr<Action>> stack;

    Action templateAction{reader, memo, context, stack};
    IterateSynonym action(templateAction, "s");

    {
        auto counter = std::make_shared<Mock::CounterAction>(templateAction);
        stack.push(counter);
        action.doAction();

        REQUIRE(context.result.size() == 13);
        for (int i = 1; i <= 13; i++) {
            REQUIRE(context.result.count(std::to_string(i)) == 1);
        }
        context.result.clear();
        assert(context.result.empty());
        stack.pop();
    }

    auto action1 = std::make_shared<IterateSynonym>(templateAction, "v");
    {
        auto counter = std::make_shared<Mock::CounterAction>(templateAction);
        stack.push(counter);
        stack.push(action1);
        action.doAction();

        REQUIRE(context.result.size() == 39);
        for (int i = 1; i <= 39; i++) {
            REQUIRE(context.result.count(std::to_string(i)) == 1);
        }
        context.result.clear();
        assert(context.result.empty());
        stack.pop();
        stack.pop();
    }
}