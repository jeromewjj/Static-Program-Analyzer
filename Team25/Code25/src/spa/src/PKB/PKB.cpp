#include "PKB.h"

PKB::PKB() {
    entityStore = std::make_shared<EntityStore>();
    followsStore = std::make_shared<FollowsStore>();
    modifiesStore = std::make_shared<ModifiesStore>();
    parentStore = std::make_shared<ParentStore>();
    statementStore = std::make_shared<StatementStore>();
    usesStore = std::make_shared<UsesStore>();
    assignPatternStore = std::make_shared<AssignPatternStore>();
    callsStore = std::make_shared<CallsStore>();
    cfgStore = std::make_shared<CFGStore>();
    ifStatementStore = std::make_shared<IfStatementStore>();
    whileStatementStore = std::make_shared<WhileStatementStore>();
    nextStore = std::make_shared<NextStore>();
    affectStore = std::make_shared<AffectStore>();
}

PKB::AffectSet PKB::generateAffectRelation() {
    auto assignStmtSet = statementStore->getStmtNum(StatementType::ASSIGN);
    AffectSet result;

    for (int assignStmt : assignStmtSet) {
        generateAffectRelationFromStmt(result, assignStmtSet, assignStmt);
    }

    return result;
}

void PKB::generateAffectRelationFromStmt(AffectSet& result, std::unordered_set<int>& assignStmtSet,
                                         StmtNum assignStmt) {
    std::unordered_set<int> visited;
    std::vector<int> stack;
    auto startingSet = nextStore->getNext(assignStmt);
    for (auto stmt : startingSet) {
        stack.emplace_back(stmt);
    }
    auto modifiedVariables = modifiesStore->getVarModifiedByStmt(assignStmt);

    while (!stack.empty()) {
        int stmt = stack[0];
        stack.erase(stack.begin());

        if (visited.find(stmt) != visited.end()) {
            continue;
        }

        visited.insert(stmt);

        StatementType stmtType = statementStore->getStmtType(stmt);

        if (stmtType == StatementType::ASSIGN) {
            auto curUsedVariables = usesStore->getVarUsedByStmt(stmt);
            if (hasCommonValue(modifiedVariables, curUsedVariables)) {
                result.insert({assignStmt, stmt});
            }
        }

        if (stmtType == StatementType::ASSIGN or stmtType == StatementType::READ or stmtType == StatementType::CALL) {
            auto curModifiesVariables = modifiesStore->getVarModifiedByStmt(stmt);
            if (hasCommonValue(modifiedVariables, curModifiesVariables)) {
                continue;
            }
        }

        auto nextStmtSet = nextStore->getNext(stmt);

        for (const auto nextStmt : nextStmtSet) {
            if (visited.find(nextStmt) == visited.end()) {
                stack.emplace_back(nextStmt);
            }
        }
    }
}

bool PKB::hasCommonValue(const std::unordered_set<std::string>& set1, const std::unordered_set<std::string>& set2) {
    for (const auto value : set1) {
        if (set2.find(value) != set2.end()) {
            return true; // A common value is found
        }
    }
    return false; // No common value found
}
