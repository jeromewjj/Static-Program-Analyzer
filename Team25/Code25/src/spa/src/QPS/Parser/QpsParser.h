#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "QPS/Argument/Tuple.h"
#include "QPS/Clause/CondClause.h"
#include "QPS/Clause/PatClause.h"
#include "QPS/Clause/STClause.h"
#include "QPS/Clause/WithClause/WithClause.h"
#include "QPS/Declaration/Declaration.h"
#include "QPS/Parser/Handlers/AndHandler.h"
#include "QPS/Parser/Handlers/Handler.h"
#include "QPS/Parser/Handlers/PatHandler.h"
#include "QPS/Parser/Handlers/STHandler.h"
#include "QPS/Parser/Handlers/WithHandler.h"
#include "QPS/Parser/ParserUtil.h"
#include "QPS/QPSException/SyntacticException.h"
#include "QPS/QPSGrammarUtil.h"
#include "QPS/Query/Query.h"
#include "QPS/Tokenizer/QpsToken.h"
#include "QPS/Tokenizer/QpsTokenizer.h"

class QpsParser {
public:
    QpsParser();
    Query parseQuery(std::string& queryInput);
    void handlePotentialDeclaration(const std::vector<QpsToken>& tokens, size_t& currentIndex,
                                    std::vector<Declaration>& declarations);
    bool isExistingDeclaration(const std::string& syn, std::vector<Declaration>& declarations);
    std::unique_ptr<SelClause> handlePotentialSelect(const std::vector<QpsToken>& tokens, size_t& currentIndex,
                                                     std::vector<Declaration>& declarations);
    std::shared_ptr<Tuple> generateTuple(const std::vector<QpsToken>& tokens, size_t& currentIndex);

private:
    std::unordered_map<std::string, EntityType> validEntities;
    std::unique_ptr<QpsTokenizer> tokenizer;
};