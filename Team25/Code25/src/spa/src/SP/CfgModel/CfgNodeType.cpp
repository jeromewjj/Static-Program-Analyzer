#include "CfgNodeType.h"

std::string cfgNodeTypeToString(CfgNodeType type) {
    if (type == CfgNodeType::NORMAL) {
        return "Normal";
    }
    else if (type == CfgNodeType::CONDITIONAL) {
        return "Conditional";
    }
    else {
        return "End";
    }
};