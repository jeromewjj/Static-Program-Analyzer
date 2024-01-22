#include "Handler.h"
#include "PatHandler.h"
#include "QPS/Clause/CondClause.h"
#include "QPS/QPSException/SyntacticException.h"
#include "QPS/QPSGrammarUtil.h"
#include "STHandler.h"
#include "WithHandler.h"

class AndHandler : public Handler {
private:
    std::vector<QpsToken> tokens;
    size_t currentIndex;
    std::string prevClauseType;
    std::vector<Declaration> declarations;
    std::string query;

public:
    AndHandler(std::vector<QpsToken>& tokens, size_t& currentIndex, std::string& prevClauseType,
               std::vector<Declaration>& declarations, std::string& query)
        : tokens(tokens), currentIndex(currentIndex), prevClauseType(prevClauseType), declarations(declarations),
          query(query){};
    virtual std::unique_ptr<CondClause> handle(std::vector<QpsToken>& tokens, size_t& currentIndex) override;
};