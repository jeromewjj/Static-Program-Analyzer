#include "UsesStore.h"

void UsesStore::setStmtUsesRelationships(StmtUsesSet stmtUsesSet) {
    for (const auto& pair : stmtUsesSet) {
        stmtUsesStore.insert(pair.first, pair.second);
    }
}

void UsesStore::setProcUsesRelationships(ProcUsesSet procUsesSet) {
    for (const auto& pair : procUsesSet) {
        procUsesStore.insert(pair.first, pair.second);
    }
}

UsesStore::VarSet UsesStore::getVarUsedByStmt(StmtNum stmtNum) {
    return stmtUsesStore.getValues(stmtNum);
}

UsesStore::VarSet UsesStore::getVarUsedByProc(Procedure proc) {
    return procUsesStore.getValues(proc);
}

UsesStore::StmtSet UsesStore::getStmtsUsedVar(Variable var) {
    return stmtUsesStore.getKeys(var);
}

UsesStore::ProcSet UsesStore::getProcsUsedVar(Variable var) {
    return procUsesStore.getKeys(var);
}

UsesStore::StmtSet UsesStore::getAllStmtsThatUse() {
    return stmtUsesStore.getAllKeys();
}

UsesStore::ProcSet UsesStore::getAllProcsThatUse() {
    return procUsesStore.getAllKeys();
}

UsesStore::VarSet UsesStore::getAllUsedVarsByStmts() {
    return stmtUsesStore.getAllValues();
}

UsesStore::VarSet UsesStore::getAllUsedVarsByProcs() {
    return procUsesStore.getAllValues();
}

bool UsesStore::containStmtUsesRelation(StmtNum stmtNum, Variable var) {
    return stmtUsesStore.containsKeyValuePair(stmtNum, var);
}

bool UsesStore::containProcUsesRelation(Procedure proc, Variable var) {
    return procUsesStore.containsKeyValuePair(proc, var);
}

bool UsesStore::containStmtUsesRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return stmtUsesStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return stmtUsesStore.containsValue(secondArg.str);
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return stmtUsesStore.containsKey(std::stoi(firstArg.str));
    }

    return stmtUsesStore.containsKeyValuePair(std::stoi(firstArg.str), secondArg.str);
}

bool UsesStore::containProcUsesRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return procUsesStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return procUsesStore.containsValue(secondArg.str);
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return procUsesStore.containsKey(firstArg.str);
    }

    return procUsesStore.containsKeyValuePair(firstArg.str, secondArg.str);
}