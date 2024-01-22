#include "WhileStatementStore.h"

void WhileStatementStore::setWhileStatements(const WhileStatementStore::WhileSet& whileSet) {
    // Insert while statement number with its condition into the while storage.
    for (const auto& whilePair : whileSet) {
        // whilePair.first is the statement number and whilePair.second is variable in the condition.
        whileStore.insert(whilePair.first, whilePair.second);
    }
}

bool WhileStatementStore::containsWhilePattern(WhileStatementStore::StmtNum stmtNum, Argument firstArg) {
    // to check if the argument is a variable or a wildcard.
    if (firstArg.type != ArgType::WILDCARD) {
        if (!whileStore.containsKeyValuePair(stmtNum, firstArg.str)) {
            return false;
        }
    }
    return whileStore.containsKey(stmtNum);
}