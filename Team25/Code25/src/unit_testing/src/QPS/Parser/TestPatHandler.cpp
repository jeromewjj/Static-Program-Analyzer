#include "../Mocks.h"
#include "QPS/Evaluator/Entity/Entity.h"
#include "QPS/Parser/Handlers/PatHandler.h"
#include "catch.hpp"

TEST_CASE("Test PatHandler") {
    std::vector<QpsToken> tokens;
    size_t currentIndex = 0;
    bool isAnd = false;
    auto declarations = Mock::Declarations();

    SECTION("Valid Handling Of Pattern") {
        // Valid Pattern Clause
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),
                  QpsToken("a", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"( _"x"_)", QpsTokenType::ALPHANUM),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        PatHandler patHandler = PatHandler(tokens, currentIndex, declarations, isAnd);
        std::unique_ptr<CondClause> condClause = patHandler.handle(tokens, currentIndex);
        PatClause* patClause = dynamic_cast<PatClause*>(condClause.get());

        REQUIRE(patClause->synPat.str == "a");
        REQUIRE(patClause->synPat.type == ArgType::SYNONYM);
        REQUIRE(patClause->entRef.str == "s");
        REQUIRE(patClause->entRef.type == ArgType::SYNONYM);
        REQUIRE(patClause->exprSpec.str == R"/(_"(x)"_)/");
        REQUIRE(patClause->exprSpec.type == ArgType::WILDCARD_EXPR);
        REQUIRE(patClause->patType == EntityType::ASSIGN);
        REQUIRE_FALSE(patClause->isNot);

        // Valid Pattern Clause containing exprSpec without wildcard
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),
                  QpsToken("a", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"( "x")", QpsTokenType::ALPHANUM),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        condClause = patHandler.handle(tokens, currentIndex);
        patClause = dynamic_cast<PatClause*>(condClause.get());

        REQUIRE(patClause->synPat.str == "a");
        REQUIRE(patClause->synPat.type == ArgType::SYNONYM);
        REQUIRE(patClause->entRef.str == "s");
        REQUIRE(patClause->entRef.type == ArgType::SYNONYM);
        REQUIRE(patClause->exprSpec.str == R"/("(x)")/");
        REQUIRE(patClause->exprSpec.type == ArgType::EXPRESSION);
        REQUIRE(patClause->patType == EntityType::ASSIGN);
        REQUIRE_FALSE(patClause->isNot);

        // Valid Pattern Clause containing while design entity
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),
                  QpsToken("w", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_)", QpsTokenType::UNDERSCORE),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        condClause = patHandler.handle(tokens, currentIndex);
        patClause = dynamic_cast<PatClause*>(condClause.get());

        REQUIRE(patClause->synPat.str == "w");
        REQUIRE(patClause->synPat.type == ArgType::SYNONYM);
        REQUIRE(patClause->entRef.str == "s");
        REQUIRE(patClause->entRef.type == ArgType::SYNONYM);
        REQUIRE(patClause->exprSpec.str == R"(_)");
        REQUIRE(patClause->exprSpec.type == ArgType::WILDCARD);
        REQUIRE(patClause->patType == EntityType::WHILE);
        REQUIRE_FALSE(patClause->isNot);

        // Valid Pattern Clause containing if design entity
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),
                  QpsToken("i", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_)", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_)", QpsTokenType::ALPHANUM),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        condClause = patHandler.handle(tokens, currentIndex);
        patClause = dynamic_cast<PatClause*>(condClause.get());

        REQUIRE(patClause->synPat.str == "i");
        REQUIRE(patClause->synPat.type == ArgType::SYNONYM);
        REQUIRE(patClause->entRef.str == "s");
        REQUIRE(patClause->entRef.type == ArgType::SYNONYM);
        REQUIRE(patClause->exprSpec.str == R"(_)");
        REQUIRE(patClause->exprSpec.type == ArgType::WILDCARD);
        REQUIRE(patClause->patType == EntityType::IF);
        REQUIRE_FALSE(patClause->isNot);

        // Valid Pattern Clause with 'not'
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM), QpsToken("not", QpsTokenType::NOT),
                  QpsToken("i", QpsTokenType::ALPHANUM),       QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::ALPHANUM),       QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_)", QpsTokenType::ALPHANUM),    QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_)", QpsTokenType::ALPHANUM),    QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        condClause = patHandler.handle(tokens, currentIndex);
        patClause = dynamic_cast<PatClause*>(condClause.get());

        REQUIRE(patClause->synPat.str == "i");
        REQUIRE(patClause->synPat.type == ArgType::SYNONYM);
        REQUIRE(patClause->entRef.str == "s");
        REQUIRE(patClause->entRef.type == ArgType::SYNONYM);
        REQUIRE(patClause->exprSpec.str == R"(_)");
        REQUIRE(patClause->exprSpec.type == ArgType::WILDCARD);
        REQUIRE(patClause->patType == EntityType::IF);
        REQUIRE(patClause->isNot);
    }

    SECTION("Invalid Handling Of Pattern") {
        auto declarations = Mock::Declarations();

        // Missing Comma
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),       QpsToken("a", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),     QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(R"(_"x + y\"_)", QpsTokenType::ALPHANUM), QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};
        PatHandler patHandler = PatHandler(tokens, currentIndex, declarations, isAnd);

        try {
            std::unique_ptr<CondClause> condClause = patHandler.handle(tokens, currentIndex);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }

        // Missing Synonym
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM), QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken(R"(_"x + y"_)", QpsTokenType::ALPHANUM), QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};

        try {
            std::unique_ptr<CondClause> condClause = patHandler.handle(tokens, currentIndex);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }

        // Missing EntRef
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),      QpsToken("a", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),    QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_"x + y"_)", QpsTokenType::ALPHANUM), QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};

        try {
            std::unique_ptr<CondClause> condClause = patHandler.handle(tokens, currentIndex);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }

        // Invalid Synonym. g does not exist as a declaration
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),
                  QpsToken("g", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::CONST),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_"x + y"_)", QpsTokenType::ALPHANUM),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};

        try {
            std::unique_ptr<CondClause> condClause = patHandler.handle(tokens, currentIndex);
        } catch (SemanticException& e) {
            REQUIRE(e.what() == "SemanticError");
        }

        // Invalid EntRef
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),
                  QpsToken("a", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken("123", QpsTokenType::CONST),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};

        try {
            std::unique_ptr<CondClause> condClause = patHandler.handle(tokens, currentIndex);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }

        // Invalid ExprSpec
        currentIndex = 0;
        tokens = {QpsToken("pattern", QpsTokenType::ALPHANUM),
                  QpsToken("a", QpsTokenType::ALPHANUM),
                  QpsToken("(", QpsTokenType::LEFT_PARENTHESIS),
                  QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),
                  QpsToken(R"(_"1 + y")", QpsTokenType::ALPHANUM),
                  QpsToken(")", QpsTokenType::RIGHT_PARENTHESIS)};

        try {
            std::unique_ptr<CondClause> condClause = patHandler.handle(tokens, currentIndex);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }
    }
}