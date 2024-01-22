#pragma once
#include <string>

namespace RelOperator {
    const std::string LESS_THAN = "<";
    const std::string LESS_THAN_OR_EQUALS = "<=";
    const std::string GREATER_THAN = ">";
    const std::string GREATER_THAN_OR_EQUALS = ">=";
    const std::string EQUALS = "==";
    const std::string NOT_EQUALS = "!=";
    const std::string AND = "&&";
    const std::string OR = "||";
};

namespace BinaryExprOperator {
    const std::string ADD = "+";
    const std::string SUBTRACT = "-";
    const std::string MULTIPLY = "*";
    const std::string DIVIDE = "/";
    const std::string MOD = "%";
};

namespace UnaryExprOperator {
    const std::string NOT = "!";
};