
#include <functional>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Argument/Argument.h"
#include "QPS/Evaluator/Entity/Entity.h"

using PKBPatternHandler = std::function<bool(const PKBReader&, const Entity&, const std::vector<Argument>&)>;

using PKBPatternMap = std::unordered_map<EntityType, PKBPatternHandler>;

namespace PKBPattern {
    extern const PKBPatternMap HANDLERS;
}
