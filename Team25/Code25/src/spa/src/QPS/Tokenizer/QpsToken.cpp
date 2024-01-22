//
// Created by Shezad Hassan on 6/9/23.
//

#include "QpsToken.h"

QpsToken::QpsToken(std::string val, QpsTokenType t) : value(std::move(val)), type(t) {}

// Implement the getter functions
std::string QpsToken::getValue() const {
    return value;
}

QpsTokenType QpsToken::getType() const {
    return type;
}
