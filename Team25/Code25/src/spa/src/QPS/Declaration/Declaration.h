#ifndef SPA_DECLARATION_H
#define SPA_DECLARATION_H

#pragma once

#include <stdexcept>
#include <string>

#include "QPS/Evaluator/Entity/Entity.h"

struct Declaration {
    const EntityType entityType;
    const std::string synonym;
};

#endif // SPA_DECLARATION_H
