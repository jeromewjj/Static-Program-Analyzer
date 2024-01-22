#ifndef SPA_WITHHANDLER_H
#define SPA_WITHHANDLER_H

#include "Handler.h"
#include "QPS/Clause/WithClause/WithClause.h"
#include "QPS/QPSException/SyntacticException.h"
#include "QPS/QPSGrammarUtil.h"

class WithHandler : public Handler {
public:
    std::vector<QpsToken> tokens;
    size_t currentIndex;
    bool isAnd;

    WithHandler(std::vector<QpsToken>& tokens, size_t& currentIndex, bool& isAnd)
        : tokens(tokens), currentIndex(currentIndex), isAnd(isAnd){};
    virtual std::unique_ptr<CondClause> handle(std::vector<QpsToken>& tokens, size_t& currentIndex) override;
};

#endif // SPA_WITHHANDLER_H
