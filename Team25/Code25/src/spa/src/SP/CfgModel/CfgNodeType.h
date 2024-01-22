#pragma once
#include <string>

enum class CfgNodeType {
    NORMAL,
    CONDITIONAL,
    END,
};

std::string cfgNodeTypeToString(CfgNodeType type);
