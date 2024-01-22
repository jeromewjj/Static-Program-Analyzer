#include <unordered_map>
#include <unordered_set>

#include "Entity.h"

#ifndef SPA_ATTRIBUTE_H
#define SPA_ATTRIBUTE_H

namespace Attribute {
    enum class ValType {
        STRING,
        INT
    };

    enum class Attribute {
        STMT_NUM,
        CONST_VALUE,
        VAR_NAME,
        PROC_NAME
    };

    extern std::unordered_map<EntityType, std::unordered_set<Attribute>> ENT_TO_ATTR;

    extern std::unordered_map<Attribute, ValType> ATTR_TO_VAL;

    extern std::unordered_map<std::string, Attribute> RAW_TO_ATTR;
}

#endif // SPA_ATTRIBUTE_H
