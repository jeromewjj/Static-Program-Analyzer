#include "../../Mocks.h"
#include "QPS/Evaluator/Action/Strategy/ClauseStrategy.h"
#include "catch.hpp"

TEST_CASE("Test NotStrategy") {
    PKB pkb;
    Mock::MockPKBReader reader{pkb};
    Context context;

    auto strategy = std::make_shared<Mock::MockFalseStrategy>();
    auto notStrategy = std::make_shared<NotStrategy>(strategy);

    REQUIRE(notStrategy->execute(reader, context));
}