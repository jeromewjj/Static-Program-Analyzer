
#include "PatClause.h"

#include <functional>

#include "QPS/Evaluator/DataStructure/Context.h"
#include "QPS/Evaluator/PKBReaderHandler/PatternHandler.h"

std::vector<std::string> PatClause::getSynonyms() {
    std::vector<std::string> temp;
    temp.push_back(synPat.str);
    if (entRef.type == ArgType::SYNONYM) {
        temp.push_back(entRef.str);
    }
    return temp;
}

std::shared_ptr<ClauseStrategy> PatClause::getStrat() {
    std::vector<Argument> args{entRef, exprSpec};
    auto strategy = std::make_shared<PatStrategy>(synPat.str, args);
    return strategy;
}

void PatClause::visit(Rulebook& rulebook) {
    rulebook.testPatClause({synPat, entRef, exprSpec});
}
