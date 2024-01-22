

#include "Attribute.h"

namespace Attribute {
    std::unordered_map<EntityType, std::unordered_set<Attribute>> ENT_TO_ATTR = {
        {EntityType::PROCEDURE, {Attribute::PROC_NAME}},
        {EntityType::CALL, {Attribute::STMT_NUM, Attribute::PROC_NAME}},
        {EntityType::VARIABLE, {Attribute::VAR_NAME}},
        {EntityType::READ, {Attribute::STMT_NUM, Attribute::VAR_NAME}},
        {EntityType::PRINT, {Attribute::STMT_NUM, Attribute::VAR_NAME}},
        {EntityType::CONSTANT, {Attribute::CONST_VALUE}},
        {EntityType::STATEMENT, {Attribute::STMT_NUM}},
        {EntityType::WHILE, {Attribute::STMT_NUM}},
        {EntityType::IF, {Attribute::STMT_NUM}},
        {EntityType::ASSIGN, {Attribute::STMT_NUM}}};

    std::unordered_map<Attribute, ValType> ATTR_TO_VAL = {
        {Attribute::PROC_NAME, ValType::STRING},
        {Attribute::VAR_NAME, ValType::STRING},
        {Attribute::STMT_NUM, ValType::INT},
        {Attribute::CONST_VALUE, ValType::INT},
    };

    std::unordered_map<std::string, Attribute> RAW_TO_ATTR = {
        {"varName", Attribute::VAR_NAME},
        {"procName", Attribute::PROC_NAME},
        {"value", Attribute::CONST_VALUE},
        {"stmt#", Attribute::STMT_NUM},
    };
}