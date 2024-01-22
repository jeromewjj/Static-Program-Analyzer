#include "PKB/Stores/CallsStore.h"
#include "catch.hpp"

TEST_CASE("setCallsRelationships sets calls relationships correctly", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    REQUIRE(callsStore.containCallsRelation("A", "B") == true);
    REQUIRE(callsStore.containCallsRelation("B", "C") == true);
    REQUIRE(callsStore.containCallsRelation("C", "D") == false);
}

TEST_CASE("setCallsRelationships sets calls stmt procedure relationships correctly", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsStmtSet callsSet = {{"A", 1}, {"B", 2}};
    callsStore.setCallsStmtRelationship(callsSet);

    REQUIRE(callsStore.getProcedureCalled(1) == "A");
    REQUIRE(callsStore.getProcedureCalled(2) == "B");
}

TEST_CASE("getCallers returns the correct callers", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    CallsStore::ProcSet callersOfA = callsStore.getCallers("A");
    REQUIRE(callersOfA.count("A") == 0);
    REQUIRE(callersOfA.count("B") == 0);
    REQUIRE(callersOfA.count("C") == 0);
    CallsStore::ProcSet callersOfB = callsStore.getCallers("B");
    REQUIRE(callersOfB.count("A") == 1);
    REQUIRE(callersOfB.count("B") == 0);
    REQUIRE(callersOfB.count("C") == 0);
    CallsStore::ProcSet callersOfC = callsStore.getCallers("C");
    REQUIRE(callersOfC.count("A") == 0);
    REQUIRE(callersOfC.count("B") == 1);
    REQUIRE(callersOfC.count("C") == 0);
}

TEST_CASE("getCallerStars returns the correct caller stars", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    CallsStore::ProcSet callerStarsOfA = callsStore.getCallerStars("A");
    REQUIRE(callerStarsOfA.count("A") == 0);
    REQUIRE(callerStarsOfA.count("B") == 0);
    REQUIRE(callerStarsOfA.count("C") == 0);
    CallsStore::ProcSet callerStarsOfB = callsStore.getCallerStars("B");
    REQUIRE(callerStarsOfB.count("A") == 1);
    REQUIRE(callerStarsOfB.count("B") == 0);
    REQUIRE(callerStarsOfB.count("C") == 0);
    CallsStore::ProcSet callerStarsOfC = callsStore.getCallerStars("C");
    REQUIRE(callerStarsOfC.count("A") == 1);
    REQUIRE(callerStarsOfC.count("B") == 1);
    REQUIRE(callerStarsOfC.count("C") == 0);
}

TEST_CASE("getCallees returns the correct callees", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    CallsStore::ProcSet calleesOfA = callsStore.getCallees("A");
    REQUIRE(calleesOfA.count("A") == 0);
    REQUIRE(calleesOfA.count("B") == 1);
    REQUIRE(calleesOfA.count("C") == 0);
    CallsStore::ProcSet calleesOfB = callsStore.getCallees("B");
    REQUIRE(calleesOfB.count("A") == 0);
    REQUIRE(calleesOfB.count("B") == 0);
    REQUIRE(calleesOfB.count("C") == 1);
    CallsStore::ProcSet calleesOfC = callsStore.getCallees("C");
    REQUIRE(calleesOfC.count("A") == 0);
    REQUIRE(calleesOfC.count("B") == 0);
    REQUIRE(calleesOfC.count("C") == 0);
}

TEST_CASE("getCalleeStars returns the correct callee stars", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    CallsStore::ProcSet calleeStarsOfA = callsStore.getCalleeStars("A");
    REQUIRE(calleeStarsOfA.count("A") == 0);
    REQUIRE(calleeStarsOfA.count("B") == 1);
    REQUIRE(calleeStarsOfA.count("C") == 1);
    CallsStore::ProcSet calleeStarsOfB = callsStore.getCalleeStars("B");
    REQUIRE(calleeStarsOfB.count("A") == 0);
    REQUIRE(calleeStarsOfB.count("B") == 0);
    REQUIRE(calleeStarsOfB.count("C") == 1);
    CallsStore::ProcSet calleeStarsOfC = callsStore.getCalleeStars("A");
    REQUIRE(calleeStarsOfC.count("A") == 0);
    REQUIRE(calleeStarsOfC.count("B") == 1);
    REQUIRE(calleeStarsOfC.count("C") == 1);
}

TEST_CASE("containCallsRelation returns true if calls relation exists", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    REQUIRE(callsStore.containCallsRelation("A", "B") == true);
    REQUIRE(callsStore.containCallsRelation("B", "C") == true);
    REQUIRE(callsStore.containCallsRelation("C", "D") == false);
}

TEST_CASE("containCallsStarRelation returns true if calls star relation exists", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    REQUIRE(callsStore.containCallsStarRelation("A", "B") == true);
    REQUIRE(callsStore.containCallsStarRelation("A", "C") == true);
    REQUIRE(callsStore.containCallsStarRelation("B", "A") == false);
    REQUIRE(callsStore.containCallsStarRelation("B", "C") == true);
    REQUIRE(callsStore.containCallsStarRelation("B", "A") == false);
}

TEST_CASE("containCallsRelation returns true if calls relation exists with Argument", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) == true);

    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "A")) == false);
    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "B")) == true);
    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "C")) == true);

    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::SYNONYM, "A"), Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::SYNONYM, "B"), Argument(ArgType::WILDCARD, "")) == true);
    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::SYNONYM, "C"), Argument(ArgType::WILDCARD, "")) == false);

    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::SYNONYM, "A"), Argument(ArgType::SYNONYM, "B")) == true);
    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::SYNONYM, "B"), Argument(ArgType::SYNONYM, "C")) == true);
    REQUIRE(callsStore.containCallsRelation(Argument(ArgType::SYNONYM, "C"), Argument(ArgType::SYNONYM, "A")) == false);
}

TEST_CASE("containCallsStarRelation returns true if calls star relation exists with Argument", "[CallsStore]") {
    CallsStore callsStore;
    CallsStore::CallsSet callsSet = {{"A", "B"}, {"B", "C"}};
    callsStore.setCallsRelationships(callsSet);

    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::WILDCARD, "")) ==
            true);

    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "A")) ==
            false);
    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "B")) ==
            true);
    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::WILDCARD, ""), Argument(ArgType::SYNONYM, "C")) ==
            true);

    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::SYNONYM, "A"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::SYNONYM, "B"), Argument(ArgType::WILDCARD, "")) ==
            true);
    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::SYNONYM, "C"), Argument(ArgType::WILDCARD, "")) ==
            false);

    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::SYNONYM, "A"), Argument(ArgType::SYNONYM, "B")) ==
            true);
    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::SYNONYM, "A"), Argument(ArgType::SYNONYM, "C")) ==
            true);
    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::SYNONYM, "B"), Argument(ArgType::SYNONYM, "C")) ==
            true);
    REQUIRE(callsStore.containCallsStarRelation(Argument(ArgType::SYNONYM, "C"), Argument(ArgType::SYNONYM, "A")) ==
            false);
}
