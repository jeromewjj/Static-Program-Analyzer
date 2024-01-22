#include "IfStatementStore.h"

void IfStatementStore::setIfStatements(const IfStatementStore::IfSet& ifSet) {
    // Insert if statement number with its condition into the if storage.
    for (const auto& ifPair : ifSet) {
        // ifPair.first is the statement number and ifPair.second is variable in the condition.
        ifStore.insert(ifPair.first, ifPair.second);
    }
}

bool IfStatementStore::containsIfPattern(IfStatementStore::StmtNum stmtNum, Argument firstArg) {
    // to check if the argument is a variable or a wildcard.
    if (firstArg.type != ArgType::WILDCARD) {
        if (!ifStore.containsKeyValuePair(stmtNum, firstArg.str)) {
            return false;
        }
    }
    return ifStore.containsKey(stmtNum);
}