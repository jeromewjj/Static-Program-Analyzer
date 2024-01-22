#import "QPS/Validator/Rules/AbstractionRules.h"
#import "catch.hpp"

TEST_CASE("Test AbstractionRules") {
    SECTION("Test expandStatementSubTypes") {
        EntityRules rule = {{EntityType::STATEMENT, EntityType::PROCEDURE}, {EntityType::PRINT, EntityType::VARIABLE}};
        std::unordered_map<AbstractionType, EntityRules> rules = {{AbstractionType::NEXT, rule}};
        rules = AbstractionRules::expandStatementSubTypes(rules);

        REQUIRE(rules.at(AbstractionType::NEXT)[0].count(EntityType::STATEMENT) == 1);
        REQUIRE(rules.at(AbstractionType::NEXT)[0].count(EntityType::ASSIGN) == 1);
        REQUIRE(rules.at(AbstractionType::NEXT)[0].count(EntityType::PROCEDURE) == 1);
        REQUIRE(rules.at(AbstractionType::NEXT)[1].count(EntityType::VARIABLE) == 1);
        REQUIRE(rules.at(AbstractionType::NEXT)[1].count(EntityType::PRINT) == 1);
        REQUIRE_FALSE(rules.at(AbstractionType::NEXT)[1].count(EntityType::ASSIGN) == 1);
        REQUIRE_FALSE(rules.at(AbstractionType::NEXT)[1].count(EntityType::STATEMENT) == 1);
    }
}
