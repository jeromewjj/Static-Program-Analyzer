//
// Created by User on 13/9/2023.
//

#include "ParserStrategy.h"
#include "QPS/Tokenizer/QpsToken.h"

class SelectStrategy : public ParserStrategy {
    void parseTokens(std::vector<QpsToken>*, int, std::vector<Declaration>*);
};