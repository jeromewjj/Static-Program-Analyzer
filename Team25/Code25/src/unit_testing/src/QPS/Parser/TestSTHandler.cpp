#include "QPS/Evaluator/Entity/Entity.h"
#include "QPS/Parser/Handlers/STHandler.h"
#include "catch.hpp"

TEST_CASE("Test handlePotentialSuchThat") {
    std::vector<QpsToken> tokens;
    size_t currentIndex = 0;
    bool isAnd = false;

    SECTION("Valid Handling Of Such That") {
        // Valid Such That
        std::string queryStr = "stmt s; var v; Select s such that Modifies(v, s)";
        tokens = {QpsToken("such", QpsTokenType::ALPHANUM),     QpsToken("that", QpsTokenType::ALPHANUM),
                  QpsToken("Modifies", QpsTokenType::ALPHANUM), QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("v", QpsTokenType::ALPHANUM),        QpsToken(",", QpsTokenType::COMMA),
                  QpsToken("s", QpsTokenType::ALPHANUM),        QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        STHandler stHandler = STHandler(tokens, currentIndex, isAnd, queryStr);
        std::unique_ptr<CondClause> stClause = stHandler.handle(tokens, currentIndex);

        REQUIRE(stClause != nullptr);
        REQUIRE_FALSE(stClause->isNot);

        // Valid Such That with 'not'
        currentIndex = 0;
        queryStr = "stmt s; var v; Select s such that not Modifies(v, s)";
        tokens = {QpsToken("such", QpsTokenType::ALPHANUM),
                  QpsToken("that", QpsTokenType::ALPHANUM),
                  QpsToken("not", QpsTokenType::NOT),
                  QpsToken("Modifies", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("v", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        stClause = stHandler.handle(tokens, currentIndex);

        REQUIRE(stClause != nullptr);
        REQUIRE(stClause->isNot);
    }

    SECTION("Invalid Handling Of Such That") {
        // Invalid Such That (Missing "that")
        currentIndex = 0;
        tokens = {QpsToken("such", QpsTokenType::ALPHANUM), QpsToken("Follows", QpsTokenType::ALPHANUM)};
        std::string queryStr = "stmt s; var v; Select s such Follows";
        STHandler stHandler = STHandler(tokens, currentIndex, isAnd, queryStr);

        try {
            std::unique_ptr<CondClause> stClause = stHandler.handle(tokens, currentIndex);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }
    }
}