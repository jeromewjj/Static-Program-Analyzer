#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/StatementStore.h"
#include "catch.hpp"

TEST_CASE("StatementStore- Basic Tests") {
    std::shared_ptr<StatementStore> statementStore = std::make_shared<StatementStore>();

    EntityTypes::STATEMENT statementOne = {READ, 1};
    EntityTypes::STATEMENT statementTwo = {
        CALL,
        12,
    };
    EntityTypes::STATEMENT statementThree = {ASSIGN, 30};

    EntityTypes::STATEMENT statementFour = {READ, 10};
    EntityTypes::STATEMENT statementFive = {CALL, 22};
    EntityTypes::STATEMENT statementSix = {ASSIGN, 15};

    StatementStore::StatementSet statementSetOne{statementOne, statementTwo, statementThree};
    StatementStore::StatementSet statementSetTwo{statementFour, statementFive, statementSix};
    //    statementStore.setStatements(statementSet);

    SECTION("Test with an Empty Statement Store") {

        REQUIRE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{});
        REQUIRE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{});
        REQUIRE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{});
        REQUIRE_FALSE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{1});
        REQUIRE_FALSE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{12});
        REQUIRE_FALSE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{30});
    }

    // insert statements into the statement store.
    statementStore->setStatements(statementSetOne);

    SECTION("Test with an Non-Empty Statement Store") {
        REQUIRE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{1});
        REQUIRE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{12});
        REQUIRE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{30});
        REQUIRE_FALSE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{});
        REQUIRE_FALSE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{});
        REQUIRE_FALSE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{});
    }

    // insert another set of statements with similar statement types.
    statementStore->setStatements(statementSetTwo);

    SECTION("Test with an Non-Empty Statement Store") {
        REQUIRE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{1, 10});
        REQUIRE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{12, 22});
        REQUIRE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{30, 15});
        REQUIRE_FALSE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{});
        REQUIRE_FALSE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{1});
        REQUIRE_FALSE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{10});
        REQUIRE_FALSE(statementStore->getStmtNum(READ) == StatementStore::StmtSet{1, 10, 22});
        REQUIRE_FALSE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{});
        REQUIRE_FALSE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{12});
        REQUIRE_FALSE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{22});
        REQUIRE_FALSE(statementStore->getStmtNum(CALL) == StatementStore::StmtSet{12, 22, 15});
        REQUIRE_FALSE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{});
        REQUIRE_FALSE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{15});
        REQUIRE_FALSE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{30});
        REQUIRE_FALSE(statementStore->getStmtNum(ASSIGN) == StatementStore::StmtSet{15, 30, 22});
    }
}