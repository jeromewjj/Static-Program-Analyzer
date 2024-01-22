#pragma once

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Mappings/BiMapOneToMany.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"
#include "PKB/Utils/StarRelationshipUtil.h"
#include "QPS/Argument/Argument.h"

class CallsStore {
public:
    using CallsSet = std::unordered_set<RelationshipTypes::CALLS_PAIR>;
    using Procedure = EntityTypes::PROCEDURE;
    using ProcSet = std::unordered_set<EntityTypes::PROCEDURE>;
    using CallsStmtSet = std::unordered_set<RelationshipTypes::CALLS_STATEMENT_PAIR>;

    /**
     * Sets a calls relationship between a set of procedure into the storage.
     *
     * @param callsSet - The set of procedure that have a calls relation amongst each other.
     */
    void setCallsRelationships(const CallsSet& callsSet);

    /**
     * Sets a calls relationship between a statement and a procedure into the storage.
     *
     * @param callsStmtSet - The set of statements-procedure pair that directly calls the procedure
     */
    void setCallsStmtRelationship(const CallsStmtSet& callsStmtSet);

    /**
     * Gets the set of procedures that calls the callee.
     *
     * @param callee - the procedure name of the callee in spotlight.
     * @return the set of procedures that called the callee.
     */
    ProcSet getCallers(Procedure callee);

    /**
     * Gets the set of procedure representing the caller that calls a given procedure directly or
     * indirectly.
     *
     * @param callee - the procedure name of the callee in spotlight.
     * @return the set of procedures that called the callee directly or indirectly.
     */
    ProcSet getCallerStars(Procedure callee);

    /**
     * Gets the set of procedures that are called by the caller.
     *
     * @param caller - the procedure name of the caller in spotlight.
     * @return the set of procedures that are called by the caller.
     */
    ProcSet getCallees(Procedure caller);

    /**
     * Gets the list of procedure representing the callee that were called by a given procedure
     * directly or indirectly.
     *
     * @param caller - the procedure name of the caller in spotlight.
     * @return the set of procedures that are called by the caller directly or indirectly.
     */
    ProcSet getCalleeStars(Procedure caller);

    /**
     * Gets the procedure that the call statement directly call
     *
     * @param stmtNum - the statement number in spotlight
     * @return the procedure that the call statement directly call
     */
    Procedure getProcedureCalled(StmtNum stmtNum);

    /**
     * Tells if a procedure-procedure pair has a calls relation between them.
     *
     * @param caller - the procedure name of the caller in spotlight.
     * @param callee - the procedure name of the callee in spotlight.
     * @return bool - the boolean answer.
     */
    bool containCallsRelation(Procedure caller, Procedure callee);

    /**
     * Tells if a procedure-procedure pair has a calls star relation between them.
     *
     * @param caller - the procedure name of the caller in spotlight.
     * @param callee - the procedure name of the callee in spotlight.
     * @return bool - the boolean answer.
     */
    bool containCallsStarRelation(Procedure caller, Procedure callee);

    /**
     * Tells if a procedure-procedure pair has a calls relation between them.
     *
     * @param firstArg - represent the caller in spotlight.
     * @param secondArg - represent the callee in spotlight.
     * @return bool - the boolean answer.
     */
    bool containCallsRelation(Argument firstArg, Argument secondArg);

    /**
     * Tells if a procedure-procedure pair has a calls star relation between them.
     *
     * @param firstArg - represent the caller in spotlight.
     * @param secondArg - represent the callee in spotlight.
     * @return bool - the boolean answer.
     */
    bool containCallsStarRelation(Argument firstArg, Argument secondArg);

private:
    BiMapManyToMany<Procedure, Procedure> callsStore;
    BiMapManyToMany<Procedure, Procedure> callsStarStore;
    BiMapOneToMany<Procedure, StmtNum> callsStmtStore;
};
