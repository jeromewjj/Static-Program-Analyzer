#pragma once

#include <unordered_set>

#include "PKB/Mappings//BiMapManyToMany.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "QPS/Argument/Argument.h"

class ModifiesStore {
public:
    using StmtModifiesSet = std::unordered_set<RelationshipTypes::STATEMENT_MODIFIES_PAIR>;
    using ProcModifiesSet = std::unordered_set<RelationshipTypes::PROCEDURE_MODIFIES_PAIR>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using Procedure = EntityTypes::PROCEDURE;
    using Variable = EntityTypes::VARIABLE;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;
    using VarSet = std::unordered_set<EntityTypes::VARIABLE>;
    using ProcSet = std::unordered_set<EntityTypes::PROCEDURE>;

    /**
     * Sets a modifies relationship between a set of statements and variables.
     *
     * @param stmtModifiesSet - The set of statements-variables modifies relationship to be stored.
     */

    void setStmtModifiesRelationships(StmtModifiesSet stmtModifiesSet);

    /**
     * Sets a modifies relationship between a set of procedures and variables.
     *
     * @param procModifiesSet - The set of procedures-variables uses relationship to be stored.
     */

    void setProcModifiesRelationships(ProcModifiesSet procModifiesSet);

    /**
     * Gets the set of variables modified by a single statement.
     *
     * @param stmtNum - the statement number of the statement in spotlight.
     * @return VarSet - the set of variables modified by the given statement.
     */

    VarSet getVarModifiedByStmt(StmtNum stmtNum);

    /**
     * Gets the set of variables modified by a single procedure.
     *
     * @param stmtNum - the procedure in spotlight.
     * @return VarSet - the set of variables modified by the given procedure.
     */

    VarSet getVarModifiedByProc(Procedure proc);

    /**
     * Gets the set of statement numbers representing the statements that modify a given variable.
     *
     * @param var - the variable in spotlight.
     * @return StmtSet - the set of statement numbers representing the statements that modify the
     * given variable.
     */

    StmtSet getStmtsModifiesVar(Variable var);

    /**
     * Gets the set of procedures that modify a given variable.
     *
     * @param var - the variable in spotlight.
     * @return Procset - the set of procedures that modify the given variable.
     */

    ProcSet getProcsModifiesVar(Variable var);

    /**
     * Gets the set of statement numbers representing all the statements that modify at least one variable.
     *
     * @return StmtSet - the set of statement numbers representing all the statements that modify at least one variable.
     */

    StmtSet getAllStmtsThatModify();

    /**
     * Gets the set of procedures that modify at least one variable.
     *
     * @return ProcSet - the set of procedures that modify at least one variable.
     */

    ProcSet getAllProcsThatModify();

    /**
     * Gets the set of variables that are modified by at least one statement number.
     *
     * @return VarSet - the set of modified variables.
     */

    VarSet getAllVarsModifiedByStmts();

    /**
     * Gets the set of variables that are modified by at least one procedure.
     *
     * @return VarSet - the set of modified variables.
     */

    VarSet getAllVarsModifiedByProcs();

    /**
     * Tells if a stmt number-variable pair has a modifies relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containStmtModifiesRelation(StmtNum stmtNum, Variable var);

    /**
     * Tells if a procedure-variable pair has a modifies relation between them.
     *
     * @return bool - the boolean answer.
     */
    bool containProcModifiesRelation(Procedure proc, Variable var);

    /**
     * Tells if a stmt number-variable pair has a modifies relation between them.
     *
     * @param firstArg - represent the statement number in spotlight.
     * @param secondArg - represent the variable in spotlight.
     * @return bool - the boolean answer.
     */
    bool containStmtModifiesRelation(Argument firstArg, Argument secondArg);

    /**
     * Tells if a procedure-variable pair has a modifies relation between them.
     *
     * @param firstArg - represent the procedure in spotlight.
     * @param secondArg - represent the variable in spotlight.
     * @return bool - the boolean answer.
     */
    bool containProcModifiesRelation(Argument firstArg, Argument secondArg);

private:
    BiMapManyToMany<StmtNum, Variable> stmtModifiesStore;
    BiMapManyToMany<Procedure, Variable> procModifiesStore;
};