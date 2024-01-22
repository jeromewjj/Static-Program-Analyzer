
#include "../../Mocks.h"
#include "QPS/Evaluator/Action/Strategy/ResultStrategy.h"
#include "catch.hpp"

TEST_CASE("Test ShortCircuit Strategy") {
    PKB pkb;
    Mock::MockPKBReader reader{pkb};

    SECTION("Test single results") {
        {
            Context context;
            context.synonymPos["x"] = Entity{"", 12, EntityType::CONSTANT};
            SingleResult strategy{{ArgType::SYNONYM, "x"}};

            context.result.insert("12");

            REQUIRE(strategy.tryShortCircuit(reader, context));
        }

        {
            Context context;
            context.synonymPos["x"] = Entity{"", 2, EntityType::CALL};
            SingleResult strategy{{ArgType::ATTRREF, "x.procName"}};

            context.result.insert("p_x");

            REQUIRE(strategy.tryShortCircuit(reader, context));
        }
    }

    SECTION("Test boolean results") {
        {
            Context context;
            BooleanResult strategy;

            strategy.write(reader, context);

            REQUIRE_FALSE(strategy.tryShortCircuit(reader, context));
        }
    }

    SECTION("Test tuple results") {
        {
            Context context;
            context.synonymPos["x"] = Entity{"", 12, EntityType::CONSTANT};
            context.synonymPos["y"] = Entity{"v1", 0, EntityType::VARIABLE};
            TupleResult strategy{{{ArgType::SYNONYM, "x"}, {ArgType::SYNONYM, "y"}}};

            context.result.insert("12 v1");

            REQUIRE(strategy.tryShortCircuit(reader, context));
        }

        {
            Context context;
            context.synonymPos["x"] = Entity{"", 12, EntityType::CONSTANT};
            context.synonymPos["y"] = Entity{"", 3, EntityType::PRINT};
            TupleResult strategy{{{ArgType::SYNONYM, "x"}, {ArgType::ATTRREF, "y.varName"}}};

            context.result.insert("12 v_z");

            REQUIRE(strategy.tryShortCircuit(reader, context));
        }
    }
}