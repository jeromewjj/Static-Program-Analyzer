#include "../Mocks.h"
#include "QPS/Evaluator/DataStructure/Context.h"
#include "catch.hpp"

// TODO: Modify to test Context & Memo separately
TEST_CASE("Test context") {
    const auto entityComparator = [](Entity& a, Entity& b) {
        if (a.name < b.name) {
            return true;
        }
        else if (a.number < b.number) {
            return true;
        }
        else {
            return a.entityType < b.entityType;
        }
    };

    SECTION("context creation") {
        REQUIRE_NOTHROW([] {
            Context context;
        });
    }
}