#include "AndHandler.h"

std::unique_ptr<CondClause> AndHandler::handle(std::vector<QpsToken>& tokens, size_t& currentIndex) {
    if (currentIndex >= tokens.size() || !isAnd(tokens[currentIndex].getValue())) {
        return nullptr;
    }
    currentIndex++;

    bool isAnd = true;

    if (prevClauseType == Constants::PATTERN_PATTERN) {
        PatHandler patHandler(tokens, currentIndex, declarations, isAnd);
        std::unique_ptr<CondClause> patClause = patHandler.handle(tokens, currentIndex);
        return patClause;
    }
    else if (prevClauseType == Constants::WITH_PATTERN) {
        WithHandler withHandler(tokens, currentIndex, isAnd);
        std::unique_ptr<CondClause> withClause = withHandler.handle(tokens, currentIndex);
        return withClause;
    }
    else {
        STHandler stHandler(tokens, currentIndex, isAnd, query);
        std::unique_ptr<CondClause> stClause = stHandler.handle(tokens, currentIndex);
        return stClause;
    }
}
