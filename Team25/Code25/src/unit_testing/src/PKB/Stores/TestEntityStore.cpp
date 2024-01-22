#include "PKB/Stores/EntityStore.h"
#include "catch.hpp"

TEST_CASE("Entity Store - Basic Test Cases") {
    std::shared_ptr<EntityStore> entityStore = std::make_shared<EntityStore>();

    EntityStore::VariableSet variableSet{"a", "b", "x", "sasha", "gloria"};

    EntityStore::ConstantSet constantSet{"1", "2", "5", "100", "22"};
    EntityStore::ProcedureSet procedureSet{"bumblebee", "T-Rex", "CS3203"};

    SECTION("Empty Stores") {
        REQUIRE(entityStore->getVariables() == EntityStore::VariableSet{});
        REQUIRE(entityStore->getConstants() == EntityStore::ConstantSet{});
        REQUIRE(entityStore->getProcedures() == EntityStore::ProcedureSet{});
        REQUIRE(entityStore->getConstant(1) == EntityStore::Constant());
        REQUIRE(entityStore->getVariable(1) == EntityStore::Variable());
        REQUIRE(entityStore->getProcedure(1) == EntityStore::Procedure());
        REQUIRE_FALSE(entityStore->getVariables() == EntityStore::VariableSet{"a", "b"});
        REQUIRE_FALSE(entityStore->getConstants() == EntityStore::ConstantSet{"1", "2"});
        REQUIRE_FALSE(entityStore->getProcedures() == EntityStore::ProcedureSet{"bumblebee", "CS3203"});
        REQUIRE_FALSE(entityStore->getConstant(1) == EntityStore::Constant("1"));
        REQUIRE_FALSE(entityStore->getVariable(1) == EntityStore::Variable("a"));
        REQUIRE_FALSE(entityStore->getProcedure(1) == EntityStore::Procedure("bumblebee"));
        ;
    }

    // set constants in the variable store
    entityStore->setConstants(constantSet);
    // set variables in the constant store
    entityStore->setVariables(variableSet);
    // set procedures in the procedure store
    entityStore->setProcedures(procedureSet);

    SECTION("Non-empty store") {
        REQUIRE(entityStore->getVariables() == EntityStore::VariableSet{"a", "b", "x", "sasha", "gloria"});
        REQUIRE(entityStore->getConstants() == EntityStore::ConstantSet{"1", "2", "5", "100", "22"});
        REQUIRE(entityStore->getProcedures() == EntityStore::ProcedureSet{"bumblebee", "T-Rex", "CS3203"});
        //        REQUIRE(entityStore->getConstant(1) == EntityStore::Constant("100"));
        //        REQUIRE(entityStore->getConstant(2) == EntityStore::Constant("5"));
        //        REQUIRE(entityStore->getVariable(1) == EntityStore::Variable("sasha"));
        //        REQUIRE(entityStore->getVariable(2) == EntityStore::Variable("x"));
        //        REQUIRE(entityStore->getVariable(3) == EntityStore::Variable("b"));
        //        REQUIRE(entityStore->getProcedure(1) == EntityStore::Procedure("CS3203"));
        REQUIRE_FALSE(entityStore->getVariables() == EntityStore::VariableSet{"a", "b"});
        REQUIRE_FALSE(entityStore->getConstants() == EntityStore::ConstantSet{"1", "2"});
        REQUIRE_FALSE(entityStore->getProcedures() == EntityStore::ProcedureSet{"bumblebee", "CS3203"});
        //        REQUIRE_FALSE(entityStore->getConstant(1) == EntityStore::Constant("1"));
        //        REQUIRE_FALSE(entityStore->getVariable(1) == EntityStore::Variable("a"));
        //        REQUIRE_FALSE(entityStore->getProcedure(1) == EntityStore::Procedure("bumblebee"));
        //        REQUIRE_FALSE(entityStore->getConstant(0) == EntityStore::Constant("100"));
        //        REQUIRE_FALSE(entityStore->getConstant(2) == EntityStore::Constant("5"));
        //        REQUIRE_FALSE(entityStore->getVariable(2) == EntityStore::Variable("sasha"));
        //        REQUIRE_FALSE(entityStore->getVariable(1) == EntityStore::Variable("x"));
        //        REQUIRE_FALSE(entityStore->getVariable(2) == EntityStore::Variable("b"));
        //        REQUIRE_FALSE(entityStore->getProcedure(0) == EntityStore::Procedure("CS3203"));
    }
}
