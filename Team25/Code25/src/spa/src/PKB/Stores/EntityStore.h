#pragma once

#include <unordered_set>

#include "PKB/Mappings/BiMapOneToOne.h"
#include "PKB/Types/EntityType.h"

class EntityStore {
public:
    using Key = EntityTypes::KEY;
    using Constant = EntityTypes::CONSTANT;
    using Variable = EntityTypes::VARIABLE;
    using Procedure = EntityTypes::PROCEDURE;
    using VariableSet = std::unordered_set<EntityTypes::VARIABLE>;
    using ConstantSet = std::unordered_set<EntityTypes::CONSTANT>;
    using ProcedureSet = std::unordered_set<EntityTypes::PROCEDURE>;

    void setConstants(const ConstantSet& constants);

    void setVariables(const VariableSet& variables);

    void setProcedures(const ProcedureSet& procedures);

    VariableSet getVariables();

    ProcedureSet getProcedures();

    ConstantSet getConstants();

    /**
     * Retrieves the constant at a particular key.
     *
     * @param key - The key at which the mapped constant is to be returned from.
     * @return A constant.
     */
    Constant getConstant(Key key);

    /**
     * Retrieves the variable at a particular key.
     *
     * @param key - The key at which the mapped variable is to be returned from.
     * @return A variable.
     */
    Variable getVariable(Key key);

    /**
     * Retrieves the procedure at a particular key.
     *
     * @param key - The key at which the mapped procedure is to be returned from.
     * @return A procedure.
     */
    Procedure getProcedure(Key key);

private:
    BiMapOneToOne<Key, Variable> variableStore;
    BiMapOneToOne<Key, Procedure> procedureStore;
    BiMapOneToOne<Key, Constant> constantStore;
};