#include "CallsStore.h"

void CallsStore::setCallsRelationships(const CallsSet& callsSet) {
    // Insert Follow relationship into Follow Store
    for (const auto& callsPair : callsSet) {
        // callsPair.first is Caller and callsPair.second is Callee
        callsStore.insert(callsPair.first, callsPair.second);
    }

    CallsSet callsStarSet = StarRelationshipUtil<Procedure>::GenerateStarRelations(callsSet);

    // Insert Calls star relationship into Calls Star Store
    for (const auto& callsPair : callsStarSet) {
        // followPair.first is Followee and followPair.second is Follower
        callsStarStore.insert(callsPair.first, callsPair.second);
    }
}

void CallsStore::setCallsStmtRelationship(const CallsStore::CallsStmtSet& callsStmtSet) {

    // Insert Follow relationship into Follow Store
    for (const auto& callsPair : callsStmtSet) {
        // callsPair.first is Caller and callsPair.second is Callee
        callsStmtStore.insert(callsPair.first, callsPair.second);
    }
}

CallsStore::ProcSet CallsStore::getCallers(Procedure callee) {
    return callsStore.getKeys(callee);
}

CallsStore::ProcSet CallsStore::getCallerStars(Procedure callee) {
    return callsStarStore.getKeys(callee);
}

CallsStore::ProcSet CallsStore::getCallees(Procedure caller) {
    return callsStore.getValues(caller);
}

CallsStore::ProcSet CallsStore::getCalleeStars(Procedure caller) {
    return callsStarStore.getValues(caller);
}

CallsStore::Procedure CallsStore::getProcedureCalled(StmtNum stmtNum) {
    return callsStmtStore.getKey(stmtNum);
}

bool CallsStore::containCallsRelation(Procedure caller, Procedure callee) {
    return callsStore.containsKeyValuePair(caller, callee);
}

bool CallsStore::containCallsStarRelation(Procedure caller, Procedure callee) {
    return callsStarStore.containsKeyValuePair(caller, callee);
}

bool CallsStore::containCallsRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return callsStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return callsStore.containsValue(secondArg.str);
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return callsStore.containsKey(firstArg.str);
    }

    return callsStore.containsKeyValuePair(firstArg.str, secondArg.str);
}

bool CallsStore::containCallsStarRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return callsStarStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return callsStarStore.containsValue(secondArg.str);
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return callsStarStore.containsKey(firstArg.str);
    }

    return callsStarStore.containsKeyValuePair(firstArg.str, secondArg.str);
}
