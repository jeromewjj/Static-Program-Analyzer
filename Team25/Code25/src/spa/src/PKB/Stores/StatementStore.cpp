#include "StatementStore.h"

void StatementStore::setStatements(const StatementSet& statements) {
    for (const auto& stmt : statements) {
        StmtNum stmtNum = stmt.stmtNum;
        StatementType stmtType = stmt.type;
        stmtTypeStore.insert(stmtType, stmtNum);
    }
}

StatementType StatementStore::getStmtType(StmtNum stmtNum) {
    return stmtTypeStore.getKey(stmtNum);
}

StatementStore::StmtSet StatementStore::getStmtNum(StatementType type) {
    return stmtTypeStore.getValues(type);
}

StatementStore::StmtSet StatementStore::getAllStmtNum() {
    return stmtTypeStore.getAllValues();
}
