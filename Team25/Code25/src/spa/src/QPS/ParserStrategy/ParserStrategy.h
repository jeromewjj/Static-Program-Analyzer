//
// Created by User on 13/9/2023.
//

#include "QPS/Declaration/Declaration.h"
#include "QPS/Tokenizer/QpsToken.h"
#include "vector"

class ParserStrategy {
public:
    virtual void parseTokens(std::vector<QpsToken>* tokens, int currentIndex, std::vector<Declaration>* declarations);
};