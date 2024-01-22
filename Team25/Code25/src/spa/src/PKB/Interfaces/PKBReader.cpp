#include "PKBReader.h"

PKBReader::PKBReader(PKB& pkb) {
    this->pkb = &pkb;
}

PKBReader::VariableSet PKBReader::getVariables() const {
    return pkb->entityStore->getVariables();
}

PKBReader::ConstantSet PKBReader::getConstants() const {
    return pkb->entityStore->getConstants();
}

PKBReader::ProcedureSet PKBReader::getProcedures() const {
    return pkb->entityStore->getProcedures();
}

StatementType PKBReader::getStmtType(StmtNum stmtNum) {
    return pkb->statementStore->getStmtType(stmtNum);
}

PKBReader::StatementSet PKBReader::getStmtNum(StatementType type) const {
    return pkb->statementStore->getStmtNum(type);
}

PKBReader::StatementSet PKBReader::getAllStmtNum() const {
    return pkb->statementStore->getAllStmtNum();
}

bool PKBReader::containFollowsRelation(StmtNum followee, StmtNum follower) const {
    return pkb->followsStore->containFollowsRelation(followee, follower);
}
bool PKBReader::containFollowsStarRelation(StmtNum followee, StmtNum follower) const {
    return pkb->followsStore->containFollowsStarRelation(followee, follower);
}

bool PKBReader::containFollowsRelation(Argument firstArg, Argument secondArg) const {
    return pkb->followsStore->containFollowsRelation(firstArg, secondArg);
}

bool PKBReader::containFollowsStarRelation(Argument firstArg, Argument secondArg) const {
    return pkb->followsStore->containFollowsStarRelation(firstArg, secondArg);
}

bool PKBReader::containParentRelation(StmtNum parent, StmtNum child) const {
    return pkb->parentStore->containParentRelation(parent, child);
}

bool PKBReader::containParentStarRelation(StmtNum parent, StmtNum child) const {
    return pkb->parentStore->containParentStarRelation(parent, child);
}

bool PKBReader::containParentRelation(Argument firstArg, Argument secondArg) const {
    return pkb->parentStore->containParentRelation(firstArg, secondArg);
}

bool PKBReader::containParentStarRelation(Argument firstArg, Argument secondArg) const {
    return pkb->parentStore->containParentStarRelation(firstArg, secondArg);
}

PKBReader::VariableSet PKBReader::getVarsUsedByStmt(StmtNum stmtNum) const {
    return pkb->usesStore->getVarUsedByStmt(stmtNum);
}

bool PKBReader::containStmtUsesRelation(StmtNum stmtNum, Variable var) const {
    return pkb->usesStore->containStmtUsesRelation(stmtNum, var);
}

bool PKBReader::containProcUsesRelation(Procedure proc, Variable var) const {
    return pkb->usesStore->containProcUsesRelation(proc, var);
}

bool PKBReader::containStmtUsesRelation(Argument firstArg, Argument secondArg) const {
    return pkb->usesStore->containStmtUsesRelation(firstArg, secondArg);
}

bool PKBReader::containProcUsesRelation(Argument firstArg, Argument secondArg) const {
    return pkb->usesStore->containProcUsesRelation(firstArg, secondArg);
}

PKBReader::VariableSet PKBReader::getVarsModifiedByStmt(StmtNum stmtNum) const {
    return pkb->modifiesStore->getVarModifiedByStmt(stmtNum);
}

bool PKBReader::containStmtModifiesRelation(StmtNum stmtNum, Variable var) const {
    return pkb->modifiesStore->containStmtModifiesRelation(stmtNum, var);
}
bool PKBReader::containProcModifiesRelation(Procedure proc, Variable var) const {
    return pkb->modifiesStore->containProcModifiesRelation(proc, var);
}

bool PKBReader::containStmtModifiesRelation(Argument firstArg, Argument secondArg) const {
    return pkb->modifiesStore->containStmtModifiesRelation(firstArg, secondArg);
}

bool PKBReader::containProcModifiesRelation(Argument firstArg, Argument secondArg) const {
    return pkb->modifiesStore->containProcModifiesRelation(firstArg, secondArg);
}

bool PKBReader::containAssignPattern(const StmtNum stmtNum, Argument firstArg, Argument secondArg) const {
    return pkb->assignPatternStore->containAssignPattern(stmtNum, firstArg, secondArg);
}

bool PKBReader::containIfPattern(const StmtNum stmtNum, Argument firstArg) const {
    return pkb->ifStatementStore->containsIfPattern(stmtNum, firstArg);
}

bool PKBReader::containWhilePattern(const StmtNum stmtNum, Argument firstArg) const {
    return pkb->whileStatementStore->containsWhilePattern(stmtNum, firstArg);
}

bool PKBReader::containCallsRelation(Procedure caller, Procedure callee) const {
    return pkb->callsStore->containCallsRelation(caller, callee);
}

bool PKBReader::containCallsStarRelation(Procedure caller, Procedure callee) const {
    return pkb->callsStore->containCallsStarRelation(caller, callee);
}

bool PKBReader::containCallsRelation(Argument firstArg, Argument secondArg) const {
    return pkb->callsStore->containCallsRelation(firstArg, secondArg);
}

bool PKBReader::containCallsStarRelation(Argument firstArg, Argument secondArg) const {
    return pkb->callsStore->containCallsStarRelation(firstArg, secondArg);
}

PKBReader::Procedure PKBReader::getProcedureCalledByStmt(PKBReaderEntityI::StmtNum stmtNum) const {
    return pkb->callsStore->getProcedureCalled(stmtNum);
}

bool PKBReader::containNextRelation(Argument firstArg, Argument secondArg) const {
    return pkb->nextStore->containNextRelation(firstArg, secondArg);
}

bool PKBReader::containNextStarRelation(Argument firstArg, Argument secondArg) const {
    return pkb->nextStore->containNextStarRelation(firstArg, secondArg);
}

bool PKBReader::containAffectRelation(Argument firstArg, Argument secondArg) const {
    if (!pkb->affectStore->checkAffectGenerated()) {
        pkb->affectStore->setAffectRelationships(pkb->generateAffectRelation());
    }
    return pkb->affectStore->containAffectRelation(firstArg, secondArg);
}

void PKBReader::clearCache() const {
    pkb->nextStore->clearNextStarStore();
    pkb->affectStore->clearAffectStore();
}