#pragma once

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Mappings/BiMapOneToMany.h"
#include "PKB/Mappings/BiMapOneToOne.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/PatternType.h"
#include "QPS/Argument/Argument.h"

class AssignPatternStore {
public:
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using StmtSet = std::unordered_set<EntityTypes::STATEMENT_NUMBER>;
    using Variable = EntityTypes::VARIABLE;
    using Expression = std::string;
    using AssignSet = std::unordered_set<Assign>;

    void setAssignPatterns(const AssignSet& assignSet);

    bool containAssignPattern(const StmtNum stmtNum, Argument firstArg, Argument secondArg);

private:
    BiMapOneToOne<StmtNum, Variable> variableStore;
    BiMapOneToMany<Expression, StmtNum> exactExpressionStore;
    BiMapManyToMany<StmtNum, Expression> partialExpressionStore;
};
