#include "SelClause.h"

#include <vector>

#include "QPS/Argument/Tuple.h"
#include "QPS/Evaluator/PKBReaderHandler/EntityHandler.h"

std::shared_ptr<ResultStrategy> SelClause::getStrategy() const {
    if (argument->type == ArgType::SYNONYM) {
        return std::make_shared<SingleResult>(*argument);
    }
    if (argument->type == ArgType::TUPLE) {
        return std::make_shared<TupleResult>(argument->getArguments());
    }
    return std::make_shared<BooleanResult>();
}
