#include "PKBWriter.h"

PKBWriter::PKBWriter(PKB& pkb) {
    this->pkb = &pkb;
}

void PKBWriter::setVariables(const VariableSet& variables) const {
    pkb->entityStore->setVariables(variables);
}

void PKBWriter::setConstants(const ConstantSet& constants) const {
    pkb->entityStore->setConstants(constants);
}

void PKBWriter::setProcedures(const ProcedureSet& procedures) const {
    pkb->entityStore->setProcedures(procedures);
}

void PKBWriter::setStatements(const StatementSet& statements) const {
    pkb->statementStore->setStatements(statements);
}

void PKBWriter::setFollowsRelationship(const FollowsSet& followSet) const {
    pkb->followsStore->setFollowsRelationships(followSet);
}

void PKBWriter::setParentsRelationship(const ParentSet& parentSet) const {
    pkb->parentStore->setParentRelationship(parentSet);
}

void PKBWriter::setStatementUsesRelationship(const StmtUsesSet& stmtUseSet) const {
    pkb->usesStore->setStmtUsesRelationships(stmtUseSet);
}

void PKBWriter::setProcedureUsesRelationship(const ProcUsesSet& procUseSet) const {
    pkb->usesStore->setProcUsesRelationships(procUseSet);
}

void PKBWriter::setStatementModifiesRelationship(const StmtModifiesSet& stmtModifiesSet) const {
    pkb->modifiesStore->setStmtModifiesRelationships(stmtModifiesSet);
}

void PKBWriter::setProcedureModifiesRelationship(const ProcModifiesSet& procModifiesSet) const {
    pkb->modifiesStore->setProcModifiesRelationships(procModifiesSet);
}

void PKBWriter::setAssignPatterns(const AssignSet& assignSet) const {
    pkb->assignPatternStore->setAssignPatterns(assignSet);
}

void PKBWriter::setIfStatements(const PKBWriter::IfSet& ifSet) const {
    pkb->ifStatementStore->setIfStatements(ifSet);
}

void PKBWriter::setWhileStatements(const PKBWriter::WhileSet& whileSet) const {
    pkb->whileStatementStore->setWhileStatements(whileSet);
}

void PKBWriter::setCallsRelationships(const CallsSet& callsSet) const {
    pkb->callsStore->setCallsRelationships(callsSet);
}

void PKBWriter::setCallsStmtRelationship(const PKBWriter::CallsStmtSet& callStmtSet) const {
    pkb->callsStore->setCallsStmtRelationship(callStmtSet);
}

void PKBWriter::setCfg(const PKBWriter::CFGBlockSet& cfgBlocks) const {
    pkb->cfgStore->setCfg(cfgBlocks);
    NextSet nextSet = pkb->cfgStore->generateNextRelation();
    pkb->nextStore->setNextRelationships(nextSet);
}