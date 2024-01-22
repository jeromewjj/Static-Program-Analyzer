#include "PKB/Stores/AssignPatternStore.h"

void AssignPatternStore::setAssignPatterns(const AssignSet& assignSet) {

    // Insert assign into Assign Pattern Store
    for (const auto& assign : assignSet) {
        variableStore.insert(assign.stmtNum, assign.var);
        exactExpressionStore.insert(assign.exactExp, assign.stmtNum);
        for (const auto& exp : assign.partialExpSet) {
            partialExpressionStore.insert(assign.stmtNum, exp);
        }
    }
}

bool AssignPatternStore::containAssignPattern(const StmtNum stmtNum, Argument firstArg, Argument secondArg) {
    if (firstArg.type != ArgType::WILDCARD && firstArg.type != ArgType::WILDCARD_EXPR) {
        if (!variableStore.containsKeyValuePair(stmtNum, firstArg.str)) {
            return false;
        }
    }

    if (secondArg.type == ArgType::EXPRESSION) {
        if (!exactExpressionStore.containsKeyValuePair(secondArg.str, stmtNum)) {
            return false;
        }
    }

    if (secondArg.type == ArgType::WILDCARD_EXPR) {
        if (!partialExpressionStore.containsKeyValuePair(stmtNum, secondArg.str)) {
            return false;
        }
    }

    return variableStore.containsKey(stmtNum);
}