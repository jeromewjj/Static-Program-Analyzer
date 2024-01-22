#pragma once

#include <string>
#include <unordered_set>

#include "PKB/Mappings//BiMapManyToMany.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "QPS/Argument/Argument.h"

class UsesStore {
public:
    using StmtUsesSet = std::unordered_set<RelationshipTypes::STATEMENT_USES_PAIR>;
    using ProcUsesSet = std::unordered_set<RelationshipTypes::PROCEDURE_USES_PAIR>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using Procedure = EntityTypes::PROCEDURE;
    using Variable = EntityTypes::VARIABLE;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;
    using VarSet = std::unordered_set<EntityTypes::VARIABLE>;
    using ProcSet = std::unordered_set<EntityTypes::PROCEDURE>;

    /**
     * Sets a uses relationship between a set of statements and variables.
     *
     * @param stmtUsesSet - The set of statements-variables uses relationship to be stored.
     */

    void setStmtUsesRelationships(StmtUsesSet stmtUsesSet);

    /**
     * Sets a uses relationship between a set of procedures and variables.
     *
     * @param procUsesSet - The set of procedures-variables uses relationship to be stored.
     */

    void setProcUsesRelationships(ProcUsesSet procUsesSet);

    /**
     * Gets the set of variables that are used by a particular statement.
     *
     * @param stmtNum - the statement number in spotlight.
     * @return VarSet - a set of variables.
     */

    VarSet getVarUsedByStmt(StmtNum stmtNum);

    /**
     * Gets the set of variables that are used by a particular procedure.
     *
     * @param proc - The procedure name in spotlight.
     * @return VarSet - a set of variables.
     */

    VarSet getVarUsedByProc(Procedure proc);

    /**
     * Gets the set of statements that use a particular variable.
     *
     * @param var - The variable in spotlight.
     * @return StmtSet - a set of statement numbers representing the statements that use a given variable.
     */

    StmtSet getStmtsUsedVar(Variable var);

    /**
     * Gets the set of statement numbers that use at least one variable.
     *
     * @return StmtSet - set of statement numbers representing the statements that use any variable.
     */

    StmtSet getAllStmtsThatUse();

    /**
     * Gets the set of procedures that use a given variable
     *
     * @param var - The variable in spotlight.
     * @return ProcSet - set of procedures that use any variable.
     */

    ProcSet getProcsUsedVar(Variable var);

    /**
     * Gets the set of procedures that use at least one variable.
     *
     * @return ProcSet - set of procedures that use any variable.
     */

    ProcSet getAllProcsThatUse();

    /**
     * Gets the set of variables used by at least one statement.
     *
     * @return VarSet - set of procedures that use any variable.
     */

    VarSet getAllUsedVarsByStmts();

    /**
     * Gets the set of variables used by at least one procedure.
     *
     * @return VarSet - set of procedures that use any variable.
     */

    VarSet getAllUsedVarsByProcs();

    /**
     * Tells if a statement-variable pair has a uses relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containStmtUsesRelation(StmtNum stmtNum, Variable var);

    /**
     * Tells if a procedure-variable pair has a uses relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containProcUsesRelation(Procedure proc, Variable var);

    /**
     * Tells if a statement-variable pair has a uses relation between them.
     *
     * @param firstArg - represent the statement number in spotlight.
     * @param secondArg - represent the variable in spotlight.
     * @return bool - the boolean answer.
     */
    bool containStmtUsesRelation(Argument firstArg, Argument secondArg);

    /**
     * Tells if a procedure-variable pair has a uses relation between them.
     *
     * @param firstArg - represent the procedure in spotlight.
     * @param secondArg - represent the variable in spotlight.
     * @return bool - the boolean answer.
     */
    bool containProcUsesRelation(Argument firstArg, Argument secondArg);

private:
    BiMapManyToMany<StmtNum, Variable> stmtUsesStore;
    BiMapManyToMany<Procedure, Variable> procUsesStore;
};