#include "../../Mocks.h"
#include "QPS/Evaluator/Action/Strategy/ResultStrategy.h"
#include "catch.hpp"

TEST_CASE("Test Write Strategy") {
    PKB pkb;
    Mock::MockPKBReader reader{pkb};

    SECTION("Test single results") {
        {
            Context context;
            context.synonymPos["x"] = Entity{"", 12, EntityType::CONSTANT};
            SingleResult strategy{{ArgType::SYNONYM, "x"}};

            strategy.write(reader, context);

            REQUIRE(context.result.count("12") == 1);
        }

        {
            Context context;
            context.synonymPos["x"] = Entity{"", 2, EntityType::CALL};
            SingleResult strategy{{ArgType::ATTRREF, "x.procName"}};

            strategy.write(reader, context);

            REQUIRE(context.result.count("p_x") == 1);
        }
    }

    SECTION("Test boolean results") {
        {
            Context context;
            BooleanResult strategy;

            strategy.write(reader, context);

            REQUIRE(context.result.count("TRUE") == 1);
        }

        {
            Context context;
            BooleanResult strategy;

            strategy.defaultWrite(context);

            REQUIRE(context.result.count("FALSE") == 1);
        }
    }

    SECTION("Test tuple results") {
        {
            Context context;
            context.synonymPos["x"] = Entity{"", 12, EntityType::CONSTANT};
            context.synonymPos["y"] = Entity{"v1", 0, EntityType::VARIABLE};
            TupleResult strategy{{{ArgType::SYNONYM, "x"}, {ArgType::SYNONYM, "y"}}};

            strategy.write(reader, context);

            REQUIRE(context.result.count("12 v1") == 1);
        }

        {
            Context context;
            context.synonymPos["x"] = Entity{"", 12, EntityType::CONSTANT};
            context.synonymPos["y"] = Entity{"", 3, EntityType::PRINT};
            TupleResult strategy{{{ArgType::SYNONYM, "x"}, {ArgType::ATTRREF, "y.varName"}}};

            strategy.write(reader, context);

            REQUIRE(context.result.count("12 v_z") == 1);
        }
    }
}