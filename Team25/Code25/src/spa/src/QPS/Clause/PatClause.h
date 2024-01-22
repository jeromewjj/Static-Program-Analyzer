#ifndef SPA_PATCLAUSE_H
#define SPA_PATCLAUSE_H

#include <string>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Clause/CondClause.h"
#include "QPS/Declaration/Declaration.h"
#include "QPS/Evaluator/DataStructure/Context.h"
#include "QPS/QPSGrammarUtil.h"

struct PatClause : CondClause {
    Argument synPat;
    Argument entRef;
    Argument exprSpec;
    EntityType patType;

public:
    explicit PatClause(const std::string& synAssign, const std::string& entRef, const std::string& exprSpec,
                       const EntityType& patType, bool isNot)
        : synPat(findsStmtRefArgType(synAssign), synAssign), entRef(findsEntRefArgType(entRef), entRef),
          exprSpec(findsExpressionSpecArgType(exprSpec), exprSpec), patType(patType) {
        this->isNot = isNot;
    };
    explicit PatClause(const Argument& synAssign, const Argument& entRef, const Argument& exprSpec)
        : synPat(synAssign), entRef(entRef), exprSpec(exprSpec){};
    std::vector<std::string> getSynonyms() override;
    std::shared_ptr<ClauseStrategy> getStrat() override;
    void visit(Rulebook& rulebook) override;
};

#endif // SPA_PATCLAUSE_H
