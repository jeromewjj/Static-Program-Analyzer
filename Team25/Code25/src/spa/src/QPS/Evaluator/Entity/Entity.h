
#ifndef SPA_ENTITY_H
#define SPA_ENTITY_H

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// need to use EntityType::XXX to use enum
// using enum class to avoid redefinition of enums from PKB
enum class EntityType {
    STATEMENT,
    READ,
    PRINT,
    CALL,
    WHILE,
    IF,
    ASSIGN,
    VARIABLE,
    CONSTANT,
    PROCEDURE
};

struct Entity {
    std::string name; // for variable, constant, procedure
    int number;       // for stmt num
    EntityType entityType;
    bool operator==(const Entity& e) const;
};

bool isStatementType(EntityType entityType);
bool isStatementEntity(const Entity& e);

#endif // SPA_ENTITY_H
