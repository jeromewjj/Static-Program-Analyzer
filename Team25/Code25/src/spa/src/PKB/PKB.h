#pragma once

#include "PKB/Stores/AffectStore.h"
#include "PKB/Stores/AssignPatternStore.h"
#include "PKB/Stores/CFGStore.h"
#include "PKB/Stores/CallsStore.h"
#include "PKB/Stores/EntityStore.h"
#include "PKB/Stores/FollowsStore.h"
#include "PKB/Stores/IfStatementStore.h"
#include "PKB/Stores/ModifiesStore.h"
#include "PKB/Stores/NextStore.h"
#include "PKB/Stores/ParentStore.h"
#include "PKB/Stores/StatementStore.h"
#include "PKB/Stores/UsesStore.h"
#include "PKB/Stores/WhileStatementStore.h"
#include "memory"

class PKB {
public:
    PKB();

    using AffectSet = std::unordered_set<RelationshipTypes::AFFECT_PAIR>;

    // Generate affect relationship
    AffectSet generateAffectRelation();

private:
    std::shared_ptr<EntityStore> entityStore;
    std::shared_ptr<FollowsStore> followsStore;
    std::shared_ptr<ModifiesStore> modifiesStore;
    std::shared_ptr<ParentStore> parentStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<UsesStore> usesStore;
    std::shared_ptr<AssignPatternStore> assignPatternStore;
    std::shared_ptr<CallsStore> callsStore;
    std::shared_ptr<CFGStore> cfgStore;
    std::shared_ptr<IfStatementStore> ifStatementStore;
    std::shared_ptr<WhileStatementStore> whileStatementStore;
    std::shared_ptr<NextStore> nextStore;
    std::shared_ptr<AffectStore> affectStore;

    friend class PKBWriter;
    friend class PKBReader;

    // Check if any of the value in the set match
    bool hasCommonValue(const std::unordered_set<std::string>& set1, const std::unordered_set<std::string>& set2);
    void generateAffectRelationFromStmt(AffectSet& affectSet, std::unordered_set<int>& assignStmtSet,
                                        StmtNum assignStmt);
};