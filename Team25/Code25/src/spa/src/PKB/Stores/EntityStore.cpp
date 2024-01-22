#include "EntityStore.h"

void EntityStore::setConstants(const ConstantSet& constants) {
    for (const auto& constant : constants) {
        constantStore.insert(constantStore.length() + 1, constant);
    }
}

void EntityStore::setVariables(const VariableSet& variables) {
    for (const auto& variable : variables) {
        variableStore.insert(variableStore.length() + 1, variable);
    }
}

void EntityStore::setProcedures(const ProcedureSet& procedures) {
    for (const auto& procedure : procedures) {
        procedureStore.insert(procedureStore.length() + 1, procedure);
    }
}

std::unordered_set<EntityStore::Variable> EntityStore::getVariables() {
    return variableStore.getAllValues();
}

std::unordered_set<EntityStore::Procedure> EntityStore::getProcedures() {
    return procedureStore.getAllValues();
}

std::unordered_set<EntityStore::Constant> EntityStore::getConstants() {
    return constantStore.getAllValues();
}

EntityStore::Constant EntityStore::getConstant(Key key) {
    return constantStore.getValue(key);
}

EntityStore::Variable EntityStore::getVariable(Key key) {
    return variableStore.getValue(key);
}

EntityStore::Procedure EntityStore::getProcedure(Key key) {
    return procedureStore.getValue(key);
}
