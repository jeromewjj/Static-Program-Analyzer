#include "../Mocks.h"
#include "QPS/Clause/PatClause.h"
#include "QPS/Clause/STClause.h"
#include "QPS/Clause/WithClause/WithClause.h"
#include "QPS/Validator/Validator.h"
#include "catch.hpp"

TEST_CASE("Test Validator") {
    Validator validator;

    auto s = std::make_shared<Argument>(ArgType::SYNONYM, "s");
    SelClause selClause(s);
    Argument arg1{ArgType::SYNONYM, "a"};
    Argument arg2{ArgType::SYNONYM, "s1"};
    Abstraction abstraction{AbstractionType::FOLLOWS, {arg1, arg2}};
    auto stClause = std::make_shared<STClause>(abstraction, true);
    Argument arg3{ArgType::SYNONYM, "v"};
    Argument arg4{ArgType::WILDCARD, ""};
    auto patClause = std::make_shared<PatClause>("a", "v", "_", EntityType::ASSIGN, false);
    auto withClause = std::make_shared<WithClause>("a.stmt#=12");
    Query query{selClause, Mock::Declarations(), {stClause.get(), patClause.get(), withClause.get()}};

    REQUIRE_NOTHROW(validator.validateQuery(query));
}