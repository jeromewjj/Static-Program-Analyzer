#pragma once

#include <unordered_set>

#include "PKB/PKB.h"
#include "PKB/Types/CFGType.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/PatternType.h"
#include "PKB/Types/RelationshipType.h"

class PKBWriter {
public:
    using VariableSet = std::unordered_set<EntityTypes::VARIABLE>;
    using ConstantSet = std::unordered_set<EntityTypes::CONSTANT>;
    using ProcedureSet = std::unordered_set<EntityTypes::PROCEDURE>;
    using StatementSet = std::unordered_set<EntityTypes::STATEMENT>;
    using FollowsSet = std::unordered_set<RelationshipTypes::FOLLOWS_PAIR>;
    using ParentSet = std::unordered_set<RelationshipTypes::PARENT_PAIR>;
    using StmtUsesSet = std::unordered_set<RelationshipTypes::STATEMENT_USES_PAIR>;
    using ProcUsesSet = std::unordered_set<RelationshipTypes::PROCEDURE_USES_PAIR>;
    using StmtModifiesSet = std::unordered_set<RelationshipTypes::STATEMENT_MODIFIES_PAIR>;
    using ProcModifiesSet = std::unordered_set<RelationshipTypes::PROCEDURE_MODIFIES_PAIR>;
    using AssignSet = std::unordered_set<Assign>;
    using CallsSet = std::unordered_set<RelationshipTypes::CALLS_PAIR>;
    using CallsStmtSet = std::unordered_set<RelationshipTypes::CALLS_STATEMENT_PAIR>;
    using CFGBlockSet = std::unordered_set<CFGBlock>;
    using IfSet = std::unordered_set<RelationshipTypes::If_PAIR>;
    using WhileSet = std::unordered_set<RelationshipTypes::WHILE_PAIR>;
    using NextSet = std::unordered_set<RelationshipTypes::NEXT_PAIR>;

    explicit PKBWriter(PKB& pkb);

    // Entity
    void setVariables(const VariableSet& variables) const;
    void setConstants(const ConstantSet& constants) const;
    void setProcedures(const ProcedureSet& procedures) const;
    void setStatements(const StatementSet& statements) const;

    // Follows
    void setFollowsRelationship(const FollowsSet& followSet) const;

    // Parents
    void setParentsRelationship(const ParentSet& parentSet) const;

    // Uses
    void setStatementUsesRelationship(const StmtUsesSet& stmtUseSet) const;
    void setProcedureUsesRelationship(const ProcUsesSet& procUseSet) const;

    // Modifies
    void setStatementModifiesRelationship(const StmtModifiesSet& stmtUseSet) const;
    void setProcedureModifiesRelationship(const ProcModifiesSet& procUseSet) const;

    // Assign Pattern
    void setAssignPatterns(const AssignSet& assignSet) const;

    // If Pattern
    void setIfStatements(const IfSet& ifSet) const;

    // While Pattern
    void setWhileStatements(const WhileSet& whileSet) const;

    // Calls
    void setCallsRelationships(const CallsSet& callsSet) const;
    void setCallsStmtRelationship(const CallsStmtSet& callStmtSet) const;

    // CFG
    void setCfg(const CFGBlockSet& cfgBlocks) const;

private:
    PKB* pkb = nullptr;
};