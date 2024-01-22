#include <functional>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Evaluator/Entity/Attribute.h"

#ifndef SPA_ATTRIBUTEHANDLER_H
#define SPA_ATTRIBUTEHANDLER_H

using PKBAttributeHandler = std::function<std::string(const PKBReader& reader, const Entity& e)>;

namespace PKBAttribute {
    extern const std::unordered_map<Attribute::Attribute, PKBAttributeHandler> HANDLERS;
}

#endif // SPA_ATTRIBUTEHANDLER_H
