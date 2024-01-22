#include "Entity.h"

#include <unordered_set>

const std::unordered_set<EntityType> STATEMENT_TYPES = {EntityType::STATEMENT, EntityType::ASSIGN, EntityType::CALL,
                                                        EntityType::PRINT,     EntityType::READ,   EntityType::IF,
                                                        EntityType::WHILE};

bool Entity::operator==(const Entity& e) const {
    return name == e.name && number == e.number && entityType == e.entityType;
}

bool isStatementType(const EntityType entityType) {
    return STATEMENT_TYPES.count(entityType) == 1;
}

bool isStatementEntity(const Entity& e) {
    return isStatementType(e.entityType);
}