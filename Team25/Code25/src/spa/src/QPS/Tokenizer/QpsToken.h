//
// Created by Shezad Hassan on 6/9/23.
//
#pragma once
#include <string>

#include "QpsTokenType.h"
using namespace Qps;

class QpsToken {
private:
    std::string value;
    QpsTokenType type;

public:
    QpsToken(std::string val, QpsTokenType t);

    // Getter functions
    std::string getValue() const;
    QpsTokenType getType() const;
};
