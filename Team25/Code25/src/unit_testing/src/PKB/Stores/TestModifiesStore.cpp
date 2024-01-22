#include "PKB/Stores/ModifiesStore.h"
#include "catch.hpp"

TEST_CASE("ModifyStore - Basic Tests") {
    std::shared_ptr<ModifiesStore> modifiesStore = std::make_shared<ModifiesStore>();

    ModifiesStore::StmtModifiesSet stmtModifiesSet{{1, "a"}, {1, "x"}, {10, "sasha"}, {20, "sasha"}, {20, "gloria"}};

    ModifiesStore::ProcModifiesSet procModifiesSet{
        {"bumblebee", "a"}, {"bumblebee", "sasha"}, {"ironhide", "x"}, {"ironhide", "gloria"}, {"spa", "b"}};

    SECTION("Set statement-variable relation function test") {
        SECTION("Empty statement store tests") {
            REQUIRE(modifiesStore->getAllStmtsThatModify() == ModifiesStore::StmtSet{});
            REQUIRE(modifiesStore->getVarModifiedByStmt(1) == ModifiesStore::VarSet{});
            REQUIRE(modifiesStore->getVarModifiedByStmt(20) == ModifiesStore::VarSet{});
            REQUIRE(modifiesStore->getVarModifiedByStmt(10) == ModifiesStore::VarSet{});
            REQUIRE(modifiesStore->getStmtsModifiesVar("a") == ModifiesStore::StmtSet{});
            REQUIRE(modifiesStore->getStmtsModifiesVar("x") == ModifiesStore::StmtSet{});
            REQUIRE(modifiesStore->getStmtsModifiesVar("sasha") == ModifiesStore::StmtSet{});
            REQUIRE(modifiesStore->getStmtsModifiesVar("gloria") == ModifiesStore::StmtSet{});
            REQUIRE(modifiesStore->getAllVarsModifiedByStmts() == ModifiesStore::VarSet{});
            REQUIRE_FALSE(modifiesStore->getStmtsModifiesVar("gloria") == ModifiesStore::StmtSet{20});
            REQUIRE_FALSE(modifiesStore->getVarModifiedByStmt(20) == ModifiesStore::VarSet{"sasha"});
            REQUIRE_FALSE(modifiesStore->getAllVarsModifiedByStmts() == ModifiesStore::VarSet{"a"});
            REQUIRE_FALSE(modifiesStore->getAllStmtsThatModify() == ModifiesStore::StmtSet{1});
        }
        modifiesStore->setStmtModifiesRelationships(stmtModifiesSet);
        SECTION("Non-empty statement store tests") {
            REQUIRE(modifiesStore->getAllStmtsThatModify() == ModifiesStore::StmtSet{1, 20, 10});
            REQUIRE(modifiesStore->getAllVarsModifiedByStmts() == ModifiesStore::VarSet{"a", "x", "sasha", "gloria"});
            REQUIRE(modifiesStore->getVarModifiedByStmt(1) == ModifiesStore::VarSet({"a", "x"}));
            REQUIRE(modifiesStore->getVarModifiedByStmt(2) == ModifiesStore::VarSet({}));
            REQUIRE(modifiesStore->getVarModifiedByStmt(10) == ModifiesStore::VarSet({"sasha"}));
            REQUIRE(modifiesStore->getVarModifiedByStmt(20) == ModifiesStore::VarSet({"sasha", "gloria"}));
            REQUIRE(modifiesStore->getStmtsModifiesVar("a") == ModifiesStore::StmtSet{1});
            REQUIRE(modifiesStore->getStmtsModifiesVar("x") == ModifiesStore::StmtSet{1});
            REQUIRE(modifiesStore->getStmtsModifiesVar("sasha") == ModifiesStore::StmtSet{10, 20});
            REQUIRE(modifiesStore->getStmtsModifiesVar("gloria") == ModifiesStore::StmtSet{20});
            REQUIRE_FALSE(modifiesStore->getVarModifiedByStmt(1) == ModifiesStore::VarSet({"b"}));
            REQUIRE_FALSE(modifiesStore->getAllStmtsThatModify() == ModifiesStore::StmtSet{1, 20, 10, 2});
            REQUIRE_FALSE(modifiesStore->getAllVarsModifiedByStmts() == ModifiesStore::VarSet{"gloria"});
            REQUIRE_FALSE(modifiesStore->getAllVarsModifiedByStmts() == ModifiesStore::VarSet{});
            REQUIRE_FALSE(modifiesStore->getStmtsModifiesVar("a") == ModifiesStore::StmtSet{});
            REQUIRE_FALSE(modifiesStore->getStmtsModifiesVar("x") == ModifiesStore::StmtSet{});
            REQUIRE_FALSE(modifiesStore->getStmtsModifiesVar("sasha") == ModifiesStore::StmtSet{});
            REQUIRE_FALSE(modifiesStore->getStmtsModifiesVar("gloria") == ModifiesStore::StmtSet{});
        }
    }

    SECTION("Set procedure-variable relation function test") {
        SECTION("Empty procedure store tests") {
            REQUIRE(modifiesStore->getAllProcsThatModify() == ModifiesStore::ProcSet{});
            REQUIRE(modifiesStore->getVarModifiedByProc("bumblebee") == ModifiesStore::VarSet{});
            REQUIRE(modifiesStore->getVarModifiedByProc("ironhide") == ModifiesStore::VarSet{});
            REQUIRE(modifiesStore->getVarModifiedByProc("spa") == ModifiesStore::VarSet{});
            REQUIRE(modifiesStore->getProcsModifiesVar("a") == ModifiesStore::ProcSet{});
            REQUIRE(modifiesStore->getAllVarsModifiedByProcs() == ModifiesStore::VarSet{});
            REQUIRE_FALSE(modifiesStore->getProcsModifiesVar("gloria") == ModifiesStore::ProcSet{"ironhide"});
            REQUIRE_FALSE(modifiesStore->getVarModifiedByProc("bumblebee") == ModifiesStore::VarSet{"sasha"});
            REQUIRE_FALSE(modifiesStore->getAllVarsModifiedByProcs() == ModifiesStore::VarSet{"a"});
        }
        modifiesStore->setProcModifiesRelationships(procModifiesSet);
        SECTION("Non-empty procedure store tests") {
            REQUIRE(modifiesStore->getAllProcsThatModify() == ModifiesStore::ProcSet{"bumblebee", "ironhide", "spa"});
            REQUIRE(modifiesStore->getAllVarsModifiedByProcs() ==
                    ModifiesStore::VarSet{"a", "x", "sasha", "gloria", "b"});
            REQUIRE(modifiesStore->getVarModifiedByProc("bumblebee") == ModifiesStore::VarSet({"a", "sasha"}));
            REQUIRE(modifiesStore->getVarModifiedByProc("abc") == ModifiesStore::VarSet({}));
            REQUIRE(modifiesStore->getVarModifiedByProc("ironhide") == ModifiesStore::VarSet({"x", "gloria"}));
            REQUIRE(modifiesStore->getVarModifiedByProc("spa") == ModifiesStore::VarSet({"b"}));
            REQUIRE(modifiesStore->getProcsModifiesVar("a") == ModifiesStore::ProcSet{"bumblebee"});
            REQUIRE(modifiesStore->getProcsModifiesVar("x") == ModifiesStore::ProcSet{"ironhide"});
            REQUIRE(modifiesStore->getProcsModifiesVar("sasha") == ModifiesStore::ProcSet{"bumblebee"});
            REQUIRE(modifiesStore->getProcsModifiesVar("gloria") == ModifiesStore::ProcSet{"ironhide"});
            REQUIRE(modifiesStore->getVarModifiedByProc("pkb") == ModifiesStore::VarSet({}));
            REQUIRE_FALSE(modifiesStore->getAllProcsThatModify() == ModifiesStore::ProcSet{"bumblebee"});
            REQUIRE_FALSE(modifiesStore->getAllVarsModifiedByProcs() == ModifiesStore::VarSet{"gloria"});
            REQUIRE_FALSE(modifiesStore->getAllVarsModifiedByProcs() == ModifiesStore::VarSet{});
        }
    }
}

TEST_CASE("containStmtModifiesRelation returns true if follow relation exists") {
    ModifiesStore modifiesStore;
    ModifiesStore::StmtModifiesSet stmtModifiesSet = {{1, "x"}, {2, "y"}};
    modifiesStore.setStmtModifiesRelationships(stmtModifiesSet);

    REQUIRE(modifiesStore.containStmtModifiesRelation(Argument(ArgType::WILDCARD, ""),
                                                      Argument(ArgType::WILDCARD, "")) == true);

    REQUIRE(modifiesStore.containStmtModifiesRelation(Argument(ArgType::SYNONYM, "1"),
                                                      Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(modifiesStore.containStmtModifiesRelation(Argument(ArgType::SYNONYM, "2"),
                                                      Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(modifiesStore.containStmtModifiesRelation(Argument(ArgType::SYNONYM, "3"),
                                                      Argument(ArgType::WILDCARD, "")) == false);

    REQUIRE(modifiesStore.containStmtModifiesRelation(Argument(ArgType::SYNONYM, "1"),
                                                      Argument(ArgType::SYNONYM, "x")) == true);
    REQUIRE(modifiesStore.containStmtModifiesRelation(Argument(ArgType::SYNONYM, "2"),
                                                      Argument(ArgType::SYNONYM, "y")) == true);
    REQUIRE(modifiesStore.containStmtModifiesRelation(Argument(ArgType::SYNONYM, "3"),
                                                      Argument(ArgType::SYNONYM, "1")) == false);
}

TEST_CASE("containProcModifiesRelation returns true if follow relation exists") {
    ModifiesStore modifiesStore;
    ModifiesStore::ProcModifiesSet procModifiesSet = {{"A", "x"}, {"B", "y"}};
    modifiesStore.setProcModifiesRelationships(procModifiesSet);

    REQUIRE(modifiesStore.containProcModifiesRelation(Argument(ArgType::WILDCARD, ""),
                                                      Argument(ArgType::WILDCARD, "")) == true);

    REQUIRE(modifiesStore.containProcModifiesRelation(Argument(ArgType::SYNONYM, "A"),
                                                      Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(modifiesStore.containProcModifiesRelation(Argument(ArgType::SYNONYM, "B"),
                                                      Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(modifiesStore.containProcModifiesRelation(Argument(ArgType::SYNONYM, "C"),
                                                      Argument(ArgType::WILDCARD, "")) == false);

    REQUIRE(modifiesStore.containProcModifiesRelation(Argument(ArgType::SYNONYM, "A"),
                                                      Argument(ArgType::SYNONYM, "x")) == true);
    REQUIRE(modifiesStore.containProcModifiesRelation(Argument(ArgType::SYNONYM, "B"),
                                                      Argument(ArgType::SYNONYM, "y")) == true);
    REQUIRE(modifiesStore.containProcModifiesRelation(Argument(ArgType::SYNONYM, "C"),
                                                      Argument(ArgType::SYNONYM, "z")) == false);
}