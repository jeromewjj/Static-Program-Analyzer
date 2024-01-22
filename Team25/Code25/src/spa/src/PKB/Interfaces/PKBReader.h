#pragma once

#include <unordered_set>

#include "PKB/PKB.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/StatementType.h"
class PKBReaderEntityI {
public:
    using Variable = EntityTypes::VARIABLE;
    using Procedure = EntityTypes::PROCEDURE;
    using Constant = EntityTypes::CONSTANT;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using VariableSet = std::unordered_set<EntityTypes::VARIABLE>;
    using ConstantSet = std::unordered_set<EntityTypes::CONSTANT>;
    using ProcedureSet = std::unordered_set<EntityTypes::PROCEDURE>;
    using StatementSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;

    [[nodiscard]] virtual VariableSet getVariables() const = 0;
    virtual ConstantSet getConstants() const = 0;
    virtual ProcedureSet getProcedures() const = 0;
    virtual StatementSet getStmtNum(StatementType type) const = 0;
    virtual StatementSet getAllStmtNum() const = 0;
};

class PKBReader : public PKBReaderEntityI {
public:
    using AffectSet = std::unordered_set<RelationshipTypes::AFFECT_PAIR>;

    explicit PKBReader(PKB& pkb);

    // Entity
    virtual VariableSet getVariables() const override;
    virtual ConstantSet getConstants() const override;
    virtual ProcedureSet getProcedures() const override;
    virtual StatementType getStmtType(StmtNum stmtNum);
    // Get a set statement number based on statement type
    virtual StatementSet getStmtNum(StatementType type) const override;
    virtual StatementSet getAllStmtNum() const override;

    // Follows
    // Check if specific Follows Relationship exist (Used for testing)
    virtual bool containFollowsRelation(StmtNum followee, StmtNum follower) const;
    // Check if specific Follows star Relationship exist (Used for testing)
    virtual bool containFollowsStarRelation(StmtNum followee, StmtNum follower) const;
    // Check if specific Follows Relationship exist
    virtual bool containFollowsRelation(Argument firstArg, Argument secondArg) const;
    // Check if specific Follows star Relationship exist
    virtual bool containFollowsStarRelation(Argument firstArg, Argument secondArg) const;

    // Parent
    // Check if specific Parent Relationship exist (Used for testing)
    virtual bool containParentRelation(StmtNum parent, StmtNum child) const;
    // Check if specific Parent star Relationship exist (Used for testing)
    virtual bool containParentStarRelation(StmtNum parent, StmtNum child) const;
    // Check if specific Parent Relationship exist
    virtual bool containParentRelation(Argument firstArg, Argument secondArg) const;
    // Check if specific Parent star Relationship exist
    virtual bool containParentStarRelation(Argument firstArg, Argument secondArg) const;

    // Uses
    // Get a set of Variables Used by Statement based on a specific statement number (USE)
    virtual VariableSet getVarsUsedByStmt(StmtNum stmtNum) const;
    // Check if specific Statement Uses Relationship exist (Used for testing)
    virtual bool containStmtUsesRelation(StmtNum stmtNum, Variable var) const;
    // Check if specific Procedure Uses Relationship exist (Used for testing)
    virtual bool containProcUsesRelation(Procedure proc, Variable var) const;
    // Check if specific Statement Uses Relationship exist
    virtual bool containStmtUsesRelation(Argument firstArg, Argument secondArg) const;
    // Check if specific Procedure Uses Relationship exist
    virtual bool containProcUsesRelation(Argument firstArg, Argument secondArg) const;

    // Modifies
    // Get a set of Variables Used by Statement based on a specific statement number (USE)
    virtual VariableSet getVarsModifiedByStmt(StmtNum stmtNum) const;
    // Check if specific Statement Modifies Relationship exist (Used for testing)
    virtual bool containStmtModifiesRelation(StmtNum stmtNum, Variable var) const;
    // Check if specific Procedure Modifies Relationship exist (Used for testing)
    virtual bool containProcModifiesRelation(Procedure proc, Variable var) const;
    // Check if specific Statement Modifies Relationship exist
    virtual bool containStmtModifiesRelation(Argument firstArg, Argument secondArg) const;
    // Check if specific Procedure Modifies Relationship exist
    virtual bool containProcModifiesRelation(Argument firstArg, Argument secondArg) const;

    // Assign Pattern
    virtual bool containAssignPattern(const StmtNum stmtNum, Argument firstArg, Argument secondArg) const;

    // If Pattern
    virtual bool containIfPattern(const StmtNum stmtNum, Argument firstArg) const;

    // While Pattern
    virtual bool containWhilePattern(const StmtNum stmtNum, Argument firstArg) const;

    // Calls
    // Check if specific Calls Relationship exist (Used for testing)
    virtual bool containCallsRelation(Procedure caller, Procedure callee) const;
    // Check if specific Calls Star Relationship exist (Used for testing)
    virtual bool containCallsStarRelation(Procedure caller, Procedure callee) const;
    // Check if specific Calls Relationship exist
    virtual bool containCallsRelation(Argument firstArg, Argument secondArg) const;
    // Check if specific Calls Star Relationship exist
    virtual bool containCallsStarRelation(Argument firstArg, Argument secondArg) const;
    // Get Procedure being called by statement (USE)
    virtual Procedure getProcedureCalledByStmt(StmtNum stmtNum) const;

    // Next
    // Check if specific Next Relationship exist
    virtual bool containNextRelation(Argument firstArg, Argument secondArg) const;
    // Check if specific Next Star Relationship exist
    virtual bool containNextStarRelation(Argument firstArg, Argument secondArg) const;

    // Affect
    // Check if specific Affect Relationship exist
    virtual bool containAffectRelation(Argument firstArg, Argument secondArg) const;

    // Clear Next Star relationship and Affect relationship
    void clearCache() const;

private:
    PKB* pkb = nullptr;
};
