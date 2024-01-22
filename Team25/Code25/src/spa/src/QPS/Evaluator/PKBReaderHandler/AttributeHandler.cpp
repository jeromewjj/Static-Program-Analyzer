
#include "AttributeHandler.h"

std::string handleStmtNum(const PKBReader& reader, const Entity& e) {
    return std::to_string(e.number);
}

std::string handleVarName(const PKBReader& reader, const Entity& e) {
    if (e.entityType == EntityType::VARIABLE) {
        return e.name;
    }

    if (e.entityType == EntityType::PRINT) {
        for (const auto& res : reader.getVarsUsedByStmt(e.number)) {
            return res;
        }
    }

    if (e.entityType == EntityType::READ) {
        for (const auto& res : reader.getVarsModifiedByStmt(e.number)) {
            return res;
        }
    }
}

std::string handleProcName(const PKBReader& reader, const Entity& e) {
    if (e.entityType == EntityType::PROCEDURE) {
        return e.name;
    }
    return reader.getProcedureCalledByStmt(e.number);
}

std::string handleValue(const PKBReader& reader, const Entity& e) {
    return e.name;
}

const std::unordered_map<Attribute::Attribute, PKBAttributeHandler> PKBAttribute::HANDLERS = {
    {Attribute::Attribute::STMT_NUM, handleStmtNum},
    {Attribute::Attribute::VAR_NAME, handleVarName},
    {Attribute::Attribute::PROC_NAME, handleProcName},
    {Attribute::Attribute::CONST_VALUE, handleValue}};
