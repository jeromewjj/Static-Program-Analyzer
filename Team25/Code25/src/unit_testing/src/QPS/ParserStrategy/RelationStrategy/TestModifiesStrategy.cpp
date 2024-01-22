#include "QPS/Argument/Argument.h"
#include "QPS/ParserStrategy/RelationStrategy/ModifiesStrategy.h"
#include "catch.hpp"

ModifiesStrategy modifiesStrategy;

TEST_CASE("Testing ModifiesStrategy parseArgs") {
    SECTION("Valid ModifiesS") {
        std::string ref1 = "stmtRef1";
        std::string ref2 = "entRef1";

        std::vector<Argument> result = modifiesStrategy.parseArgs(ref1, ref2);

        REQUIRE(result.size() == 2);
        REQUIRE(result[0].type == ArgType::SYNONYM);
        REQUIRE(result[0].str == ref1);
        REQUIRE(result[1].type == ArgType::SYNONYM);
        REQUIRE(result[1].str == ref2);
    }

    SECTION("Valid ModifiesP") {
        std::string ref1 = "\"helloThere\"";
        std::string ref2 = "\"welcome\"";

        std::vector<Argument> result = modifiesStrategy.parseArgs(ref1, ref2);

        REQUIRE(result.size() == 2);
        REQUIRE(result[0].type == ArgType::EXPRESSION);
        REQUIRE(result[0].str == ref1);
        REQUIRE(result[1].type == ArgType::EXPRESSION);
        REQUIRE(result[1].str == ref2);
    }
}