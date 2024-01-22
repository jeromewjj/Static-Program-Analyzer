#include "Token.h"

Token::Token(std::string val, TokenType t) : value(std::move(val)), type(t) {}

std::string Token::getValue() const {
    return value;
}

TokenType Token::getType() const {
    return type;
}
