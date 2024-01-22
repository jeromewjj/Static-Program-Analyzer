#include "../../Mocks.h"
#include "QPS/Evaluator/Action/WriteResult.h"
#include "catch.hpp"

TEST_CASE("Test WriteResult") {
    PKB pkb;
    Mock::MockPKBReader reader(pkb);
    Context context;
    Memo memo;
    std::stack<std::shared_ptr<Action>> stack;

    Action templateAction{reader, memo, context, stack};

    {
        context.synonymPos["s"] = {"", 12, EntityType::STATEMENT};
        auto strategy = std::make_shared<Mock::MockResultStrategy>();
        auto action = std::make_shared<WriteResult>(templateAction, strategy);

        action->doAction();
        REQUIRE(context.result.count("MOCK") == 1);
        REQUIRE(context.restartEvaluation);
    }
}