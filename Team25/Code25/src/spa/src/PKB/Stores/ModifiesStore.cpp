#include "ModifiesStore.h"

void ModifiesStore::setStmtModifiesRelationships(StmtModifiesSet stmtModifiesSet) {
    for (const auto& pair : stmtModifiesSet) {
        stmtModifiesStore.insert(pair.first, pair.second);
    }
}

void ModifiesStore::setProcModifiesRelationships(ProcModifiesSet procModifiesSet) {
    for (const auto& pair : procModifiesSet) {
        procModifiesStore.insert(pair.first, pair.second);
    }
}

ModifiesStore::VarSet ModifiesStore::getVarModifiedByStmt(StmtNum stmtNum) {
    return stmtModifiesStore.getValues(stmtNum);
}

ModifiesStore::VarSet ModifiesStore::getVarModifiedByProc(Procedure proc) {
    return procModifiesStore.getValues(proc);
}

ModifiesStore::StmtSet ModifiesStore::getStmtsModifiesVar(Variable var) {
    return stmtModifiesStore.getKeys(var);
}

ModifiesStore::ProcSet ModifiesStore::getProcsModifiesVar(Variable var) {
    return procModifiesStore.getKeys(var);
}

ModifiesStore::StmtSet ModifiesStore::getAllStmtsThatModify() {
    return stmtModifiesStore.getAllKeys();
}

ModifiesStore::ProcSet ModifiesStore::getAllProcsThatModify() {
    return procModifiesStore.getAllKeys();
}

ModifiesStore::VarSet ModifiesStore::getAllVarsModifiedByStmts() {
    return stmtModifiesStore.getAllValues();
}

ModifiesStore::VarSet ModifiesStore::getAllVarsModifiedByProcs() {
    return procModifiesStore.getAllValues();
}

bool ModifiesStore::containStmtModifiesRelation(StmtNum stmtNum, Variable var) {
    return stmtModifiesStore.containsKeyValuePair(stmtNum, var);
}

bool ModifiesStore::containProcModifiesRelation(Procedure proc, Variable var) {
    return procModifiesStore.containsKeyValuePair(proc, var);
}

bool ModifiesStore::containStmtModifiesRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return stmtModifiesStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return stmtModifiesStore.containsValue(secondArg.str);
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return stmtModifiesStore.containsKey(std::stoi(firstArg.str));
    }

    return stmtModifiesStore.containsKeyValuePair(std::stoi(firstArg.str), secondArg.str);
}

bool ModifiesStore::containProcModifiesRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return procModifiesStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return procModifiesStore.containsValue(secondArg.str);
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return procModifiesStore.containsKey(firstArg.str);
    }

    return procModifiesStore.containsKeyValuePair(firstArg.str, secondArg.str);
}
