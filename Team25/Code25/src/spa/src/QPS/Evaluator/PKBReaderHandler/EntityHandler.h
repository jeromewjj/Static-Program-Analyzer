
#include <functional>
#include <unordered_set>
#include <vector>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Evaluator/Entity/Entity.h"

using EntityReaderHandler = const std::function<std::vector<Entity>(const PKBReaderEntityI&)>;

namespace PKBEntity {
    extern const std::unordered_map<EntityType, EntityReaderHandler> HANDLERS;
}
