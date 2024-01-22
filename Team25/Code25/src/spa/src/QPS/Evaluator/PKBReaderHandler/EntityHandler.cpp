
#include "EntityHandler.h"

const auto convertStringToEntity = [](std::string s, EntityType e) {
    return Entity{s, 0, e};
};
const auto convertIntToEntity = [](int i, EntityType e) {
    return Entity{"", i, e};
};
const auto convertStrSet = [](const std::unordered_set<std::string>& set, EntityType e) {
    std::vector<Entity> res;
    for (const auto& s : set) {
        res.push_back(convertStringToEntity(s, e));
    }
    return res;
};
const auto convertIntSet = [](const std::unordered_set<int>& set, EntityType e) {
    std::vector<Entity> res;
    for (const auto& i : set) {
        res.push_back(convertIntToEntity(i, e));
    }
    return res;
};
EntityReaderHandler VarHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getVariables();
    return convertStrSet(readRes, EntityType::VARIABLE);
};
EntityReaderHandler ReadHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getStmtNum(READ);
    return convertIntSet(readRes, EntityType::READ);
};
EntityReaderHandler PrintHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getStmtNum(PRINT);
    return convertIntSet(readRes, EntityType::PRINT);
};
EntityReaderHandler CallHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getStmtNum(CALL);
    return convertIntSet(readRes, EntityType::CALL);
};
EntityReaderHandler WhileHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getStmtNum(WHILE);
    return convertIntSet(readRes, EntityType::WHILE);
};
EntityReaderHandler IfHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getStmtNum(IF);
    return convertIntSet(readRes, EntityType::IF);
};
EntityReaderHandler AssHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getStmtNum(ASSIGN);
    return convertIntSet(readRes, EntityType::ASSIGN);
};
EntityReaderHandler StmtHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getAllStmtNum();
    return convertIntSet(readRes, EntityType::STATEMENT);
};
EntityReaderHandler ConstHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getConstants();
    return convertStrSet(readRes, EntityType::CONSTANT);
};
EntityReaderHandler ProcHandler = [](const PKBReaderEntityI& reader) {
    auto readRes = reader.getProcedures();
    return convertStrSet(readRes, EntityType::PROCEDURE);
};

namespace PKBEntity {
    const std::unordered_map<EntityType, EntityReaderHandler> HANDLERS = {
        {EntityType::VARIABLE, VarHandler},  {EntityType::STATEMENT, StmtHandler}, {EntityType::READ, ReadHandler},
        {EntityType::PRINT, PrintHandler},   {EntityType::CALL, CallHandler},      {EntityType::WHILE, WhileHandler},
        {EntityType::IF, IfHandler},         {EntityType::ASSIGN, AssHandler},     {EntityType::CONSTANT, ConstHandler},
        {EntityType::PROCEDURE, ProcHandler}};
}
