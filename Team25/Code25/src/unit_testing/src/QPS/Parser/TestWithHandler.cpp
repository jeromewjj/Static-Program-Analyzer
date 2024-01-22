#include "QPS/Evaluator/Entity/Entity.h"
#include "QPS/Parser/Handlers/WithHandler.h"
#include "catch.hpp"

TEST_CASE("Test handlePotentialWith") {
    vector<QpsToken> tokens;
    size_t currentIndex = 0;
    bool isAnd = false;

    SECTION("Valid handling of With") {
        tokens = {QpsToken("with", QpsTokenType::WITH), QpsToken("'v'", QpsTokenType::ALPHANUM),
                  QpsToken("=", QpsTokenType::EQUALS), QpsToken("1", QpsTokenType::CONST)};
        WithHandler withHandler = WithHandler(tokens, currentIndex, isAnd);
        std::unique_ptr<CondClause> condClause = withHandler.handle(tokens, currentIndex);
        WithClause* withClause = dynamic_cast<WithClause*>(condClause.get());

        REQUIRE(withClause->attrCompare->leftArg.type == ArgType::EXPRESSION);
        REQUIRE(withClause->attrCompare->leftArg.str == "'v'");

        REQUIRE(withClause->attrCompare->rightArg.type == ArgType::CONSTANT);
        REQUIRE(withClause->attrCompare->rightArg.str == "1");

        REQUIRE_FALSE(withClause->isNot);
    }

    SECTION("Valid With Clause contains NOT") {
        tokens = {QpsToken("with", QpsTokenType::WITH),
                  QpsToken("not", QpsTokenType::NOT),
                  QpsToken("q", QpsTokenType::ALPHANUM),
                  QpsToken(".", QpsTokenType::DOT),
                  QpsToken("procName", QpsTokenType::ALPHANUM),
                  QpsToken("=", QpsTokenType::EQUALS),
                  QpsToken("\"funcName\"", QpsTokenType::ALPHANUM)};
        WithHandler withHandler = WithHandler(tokens, currentIndex, isAnd);
        std::unique_ptr<CondClause> condClause = withHandler.handle(tokens, currentIndex);
        WithClause* withClause = dynamic_cast<WithClause*>(condClause.get());

        REQUIRE(withClause->attrCompare->leftArg.type == ArgType::ATTRREF);
        REQUIRE(withClause->attrCompare->leftArg.str == "q.procName");

        REQUIRE(withClause->attrCompare->rightArg.type == ArgType::EXPRESSION);
        REQUIRE(withClause->attrCompare->rightArg.str == "\"funcName\"");
        REQUIRE(withClause->isNot);
    }
}