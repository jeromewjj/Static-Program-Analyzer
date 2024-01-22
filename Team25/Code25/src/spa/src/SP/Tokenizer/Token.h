//
// Created by Shezad Hassan on 6/9/23.
//

#pragma once
#include <string>

#include "TokenType.h"

class Token {
private:
    std::string value;
    TokenType type;

public:
    Token(std::string val, TokenType t);

    std::string getValue() const;
    TokenType getType() const;
};
