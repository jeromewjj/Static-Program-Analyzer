#pragma once
#include "Handler.h"
#include "QPS/Clause/PatClause.h"
#include "QPS/QPSException/SyntacticException.h"
#include "QPS/QPSGrammarUtil.h"

class PatHandler : public Handler {
private:
    std::vector<QpsToken> tokens;
    size_t currentIndex;
    std::vector<Declaration> declarations;
    bool isAnd;

public:
    PatHandler(std::vector<QpsToken>& tokens, size_t& currentIndex, std::vector<Declaration>& declarations, bool& isAnd)
        : tokens(tokens), currentIndex(currentIndex), declarations(declarations), isAnd(isAnd){};
    virtual std::unique_ptr<CondClause> handle(std::vector<QpsToken>& tokens, size_t& currentIndex) override;
    EntityType assignSynEntityType(std::vector<Declaration>& declarations, std::string synPat);
    std::string parseExprInExprSpec(std::string exprSpec);
};
