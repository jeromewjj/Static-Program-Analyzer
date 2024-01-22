#include <catch.hpp>
#include <iostream>

#include "../Mocks.h"
#include "QPS/Clause/PatClause.h"
#include "QPS/Clause/STClause.h"
#include "QPS/Evaluator/Evaluator.h"

TEST_CASE("Test Evaluator") {
    auto s = std::make_shared<Argument>(ArgType::SYNONYM, "s");
    SelClause selClause(s);
    Argument arg1{ArgType::SYNONYM, "s"};
    Argument arg2{ArgType::SYNONYM, "s1"};
    Abstraction abstraction{AbstractionType::AFFECTS, {arg1, arg2}};
    auto stClause = std::make_shared<STClause>(abstraction, true);
    Argument arg3{ArgType::SYNONYM, "v"};
    Argument arg4{ArgType::WILDCARD, ""};
    auto patClause = std::make_shared<PatClause>("a", "v", "_", EntityType::ASSIGN, false);
    Query query{selClause, Mock::Declarations(), {stClause.get(), patClause.get()}};

    PKB pkb;
    Mock::MockPKBReader reader{pkb};
    Evaluator evaluator{reader};
    for (const auto& res : evaluator.evaluateQuery(query)) {
        std::cout << res << std::endl;
    }
    std::cout << "done" << std::endl;
}