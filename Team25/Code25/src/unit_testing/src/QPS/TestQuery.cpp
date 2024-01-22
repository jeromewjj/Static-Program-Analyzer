#include "QPS/Clause/STClause.h"
#include "QPS/Evaluator/Entity/Entity.h"
#include "QPS/Query/Query.h"
#include "catch.hpp"

TEST_CASE("Query Tests") {
    std::vector<CondClause*> clauses;
    Declaration declaration1 = {EntityType::STATEMENT, "s"};
    Declaration declaration2 = {EntityType::STATEMENT, "x"};
    Declaration declaration3 = {EntityType::STATEMENT, "y"};
    Declaration declaration4 = {EntityType::ASSIGN, "a"};
    Declaration declaration5 = {EntityType::ASSIGN, "b"};

    std::vector<Argument> argList = {};
    Abstraction abstraction = Abstraction(AbstractionType::FOLLOWS, argList);
    bool isNot = false;
    STClause stClause(abstraction, isNot);
    std::unique_ptr<STClause> stClausePtr = std::make_unique<STClause>(stClause);

    SECTION("Valid Query") {
        std::vector<Declaration> declarations = {declaration1, declaration2, declaration3, declaration4, declaration5};
        clauses.push_back(stClausePtr.release());
        SelClause selClause = SelClause(std::shared_ptr<Argument>(new Argument{ArgType::SYNONYM, "q1"}));

        Query query = {selClause, declarations, clauses};

        REQUIRE(query.selClause.argument->str == "q1");
        REQUIRE(query.declarations.size() == 5);
        REQUIRE(query.clauses.size() == 1);
        REQUIRE_FALSE(query.clauses[0]->isNot);
    }
}