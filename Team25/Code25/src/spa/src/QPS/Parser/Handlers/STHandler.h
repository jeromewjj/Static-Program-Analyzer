#ifndef SPA_STHANDLER_H
#define SPA_STHANDLER_H

#include "Handler.h"
#include "QPS/Clause/STClause.h"
#include "QPS/ParserStrategy/RelationStrategyManager.h"
#include "QPS/QPSException/SyntacticException.h"
#include "QPS/QPSGrammarUtil.h"

class STHandler : public Handler {
public:
    std::vector<QpsToken> tokens;
    size_t currentIndex;
    bool isAnd;
    std::string query;

    STHandler(std::vector<QpsToken>& tokens, size_t& currentIndex, bool& isAnd, std::string& query)
        : tokens(tokens), currentIndex(currentIndex), isAnd(isAnd), query(query){};
    virtual std::unique_ptr<CondClause> handle(std::vector<QpsToken>& tokens, size_t& currentIndex) override;
};

#endif // SPA_STHANDLER_H
