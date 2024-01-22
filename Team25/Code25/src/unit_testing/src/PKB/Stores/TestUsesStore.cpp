#include "PKB/Stores/UsesStore.h"
#include "catch.hpp"

TEST_CASE("UsesStore - Basic Tests") {
    std::shared_ptr<UsesStore> usesStore = std::make_shared<UsesStore>();

    UsesStore::StmtUsesSet stmtUsesSet{{1, "a"}, {1, "x"}, {10, "sasha"}, {20, "sasha"}, {20, "gloria"}};

    UsesStore::ProcUsesSet procUsesSet{
        {"bumblebee", "a"}, {"bumblebee", "sasha"}, {"ironhide", "x"}, {"ironhide", "gloria"}, {"spa", "b"}};

    SECTION("Set statement-variable relation function test") {
        SECTION("Empty statement store tests") {
            REQUIRE(usesStore->getAllStmtsThatUse() == UsesStore::StmtSet{});
            REQUIRE(usesStore->getVarUsedByStmt(1) == UsesStore::VarSet{});
            REQUIRE(usesStore->getVarUsedByStmt(20) == UsesStore::VarSet{});
            REQUIRE(usesStore->getVarUsedByStmt(10) == UsesStore::VarSet{});
            REQUIRE(usesStore->getStmtsUsedVar("a") == UsesStore::StmtSet{});
            REQUIRE(usesStore->getAllUsedVarsByStmts() == UsesStore::VarSet{});
            REQUIRE(usesStore->containStmtUsesRelation(1, "sasha") == false);
            REQUIRE_FALSE(usesStore->getStmtsUsedVar("gloria") == UsesStore::StmtSet{20});
            REQUIRE_FALSE(usesStore->getVarUsedByStmt(20) == UsesStore::VarSet{"sasha"});
            REQUIRE_FALSE(usesStore->getAllUsedVarsByStmts() == UsesStore::VarSet{"a"});
            REQUIRE_FALSE(usesStore->getAllStmtsThatUse() == UsesStore::StmtSet{1});
        }
        usesStore->setStmtUsesRelationships(stmtUsesSet);
        SECTION("Non-empty statement store tests") {
            REQUIRE(usesStore->getAllStmtsThatUse() == UsesStore::StmtSet{1, 20, 10});
            REQUIRE(usesStore->getAllUsedVarsByStmts() == UsesStore::VarSet{"a", "x", "sasha", "gloria"});
            REQUIRE(usesStore->getVarUsedByStmt(1) == UsesStore::VarSet({"a", "x"}));
            REQUIRE(usesStore->getVarUsedByStmt(2) == UsesStore::VarSet({}));
            REQUIRE(usesStore->getVarUsedByStmt(10) == UsesStore::VarSet({"sasha"}));
            REQUIRE(usesStore->getVarUsedByStmt(20) == UsesStore::VarSet({"sasha", "gloria"}));
            REQUIRE(usesStore->getStmtsUsedVar("a") == UsesStore::StmtSet{1});
            REQUIRE(usesStore->getStmtsUsedVar("x") == UsesStore::StmtSet{1});
            REQUIRE(usesStore->getStmtsUsedVar("sasha") == UsesStore::StmtSet{10, 20});
            REQUIRE(usesStore->getStmtsUsedVar("gloria") == UsesStore::StmtSet{20});
            REQUIRE(usesStore->containStmtUsesRelation(10, "sasha") == true);
            REQUIRE(usesStore->containStmtUsesRelation(20, "sasha") == true);
            REQUIRE(usesStore->containStmtUsesRelation(20, "gloria") == true);
            REQUIRE(usesStore->containStmtUsesRelation(1, "sasha") == false);
            REQUIRE_FALSE(usesStore->getVarUsedByStmt(1) == UsesStore::VarSet({"b"}));
            REQUIRE_FALSE(usesStore->getAllStmtsThatUse() == UsesStore::StmtSet{1, 20, 10, 2});
            REQUIRE_FALSE(usesStore->getAllUsedVarsByStmts() == UsesStore::VarSet{"gloria"});
            REQUIRE_FALSE(usesStore->getAllUsedVarsByStmts() == UsesStore::VarSet{});
            REQUIRE_FALSE(usesStore->containStmtUsesRelation(10, "gloria") == true);
            REQUIRE_FALSE(usesStore->containStmtUsesRelation(1, "b") == true);
        }
    }

    SECTION("Set procedure-variable relation function test") {
        SECTION("Empty procedure store tests") {
            REQUIRE(usesStore->getAllProcsThatUse() == UsesStore::ProcSet{});
            REQUIRE(usesStore->getVarUsedByProc("bumblebee") == UsesStore::VarSet{});
            REQUIRE(usesStore->getVarUsedByProc("ironhide") == UsesStore::VarSet{});
            REQUIRE(usesStore->getVarUsedByProc("spa") == UsesStore::VarSet{});
            REQUIRE(usesStore->getProcsUsedVar("a") == UsesStore::ProcSet{});
            REQUIRE(usesStore->getAllUsedVarsByProcs() == UsesStore::VarSet{});
            REQUIRE(usesStore->containProcUsesRelation("ironhide", "gloria") == false);
            REQUIRE(usesStore->containProcUsesRelation("ironhide", "a") == false);
            REQUIRE_FALSE(usesStore->getProcsUsedVar("gloria") == UsesStore::ProcSet{"ironhide"});
            REQUIRE_FALSE(usesStore->getVarUsedByProc("bumblebee") == UsesStore::VarSet{"sasha"});
            REQUIRE_FALSE(usesStore->getAllUsedVarsByProcs() == UsesStore::VarSet{"a"});
        }
        usesStore->setProcUsesRelationships(procUsesSet);
        SECTION("Non-empty procedure store tests") {
            REQUIRE(usesStore->getAllProcsThatUse() == UsesStore::ProcSet{"bumblebee", "ironhide", "spa"});
            REQUIRE(usesStore->getAllUsedVarsByProcs() == UsesStore::VarSet{"a", "x", "sasha", "gloria", "b"});
            REQUIRE(usesStore->getVarUsedByProc("bumblebee") == UsesStore::VarSet({"a", "sasha"}));
            REQUIRE(usesStore->getVarUsedByProc("abc") == UsesStore::VarSet({}));
            REQUIRE(usesStore->getVarUsedByProc("ironhide") == UsesStore::VarSet({"x", "gloria"}));
            REQUIRE(usesStore->getVarUsedByProc("spa") == UsesStore::VarSet({"b"}));
            REQUIRE(usesStore->getProcsUsedVar("a") == UsesStore::ProcSet{"bumblebee"});
            REQUIRE(usesStore->getProcsUsedVar("x") == UsesStore::ProcSet{"ironhide"});
            REQUIRE(usesStore->getProcsUsedVar("sasha") == UsesStore::ProcSet{"bumblebee"});
            REQUIRE(usesStore->getProcsUsedVar("gloria") == UsesStore::ProcSet{"ironhide"});
            REQUIRE(usesStore->getVarUsedByProc("pkb") == UsesStore::VarSet({}));
            REQUIRE(usesStore->containProcUsesRelation("ironhide", "gloria") == true);
            REQUIRE_FALSE(usesStore->getAllProcsThatUse() == UsesStore::ProcSet{"bumblebee"});
            REQUIRE_FALSE(usesStore->getAllUsedVarsByProcs() == UsesStore::VarSet{"gloria"});
            REQUIRE_FALSE(usesStore->getAllUsedVarsByProcs() == UsesStore::VarSet{});
        }
    }
}

TEST_CASE("containStmtUsesRelation returns true if follow relation exists") {
    UsesStore usesStore;
    UsesStore::StmtUsesSet stmtUsesSet = {{1, "x"}, {2, "y"}};
    usesStore.setStmtUsesRelationships(stmtUsesSet);

    REQUIRE(usesStore.containStmtUsesRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(usesStore.containStmtUsesRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(usesStore.containStmtUsesRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(usesStore.containStmtUsesRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(usesStore.containStmtUsesRelation(Argument(ArgType::SYNONYM, "1"), Argument(ArgType::SYNONYM, "x")) ==
            true);
    REQUIRE(usesStore.containStmtUsesRelation(Argument(ArgType::SYNONYM, "2"), Argument(ArgType::SYNONYM, "y")) ==
            true);
    REQUIRE(usesStore.containStmtUsesRelation(Argument(ArgType::SYNONYM, "3"), Argument(ArgType::SYNONYM, "1")) ==
            false);
}

TEST_CASE("containProcUsesRelation returns true if follow relation exists") {
    UsesStore usesStore;
    UsesStore::ProcUsesSet procUsesSet = {{"A", "x"}, {"B", "y"}};
    usesStore.setProcUsesRelationships(procUsesSet);

    REQUIRE(usesStore.containProcUsesRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(usesStore.containProcUsesRelation(Argument(ArgType::SYNONYM, "A"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(usesStore.containProcUsesRelation(Argument(ArgType::SYNONYM, "B"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(usesStore.containProcUsesRelation(Argument(ArgType::SYNONYM, "C"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(usesStore.containProcUsesRelation(Argument(ArgType::SYNONYM, "A"), Argument(ArgType::SYNONYM, "x")) ==
            true);
    REQUIRE(usesStore.containProcUsesRelation(Argument(ArgType::SYNONYM, "B"), Argument(ArgType::SYNONYM, "y")) ==
            true);
    REQUIRE(usesStore.containProcUsesRelation(Argument(ArgType::SYNONYM, "C"), Argument(ArgType::SYNONYM, "z")) ==
            false);
}