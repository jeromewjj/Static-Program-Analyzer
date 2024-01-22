#include "ParentStore.h"

void ParentStore::setParentRelationship(const ParentSet& parentSet) {
    // Insert Parent relationship into Parent Store
    for (const auto& parentPair : parentSet) {
        // parentPair.first is Parent and parentPair.second is Child
        parentStore.insert(parentPair.first, parentPair.second);
    }

    ParentSet parentStarSet = StarRelationshipUtil<StmtNum>::GenerateStarRelations(parentSet);

    // Insert Parent star relationship into Parent Star Store
    for (const auto& parentPair : parentStarSet) {
        // parentPair.first is Parent and parentPair.second is Child
        parentStarStore.insert(parentPair.first, parentPair.second);
    }
}

ParentStore::StmtSet ParentStore::getChilds(StmtNum parent) {
    return parentStore.getValues(parent);
}

ParentStore::StmtSet ParentStore::getChildsStar(StmtNum parent) {
    return parentStarStore.getValues(parent);
}

ParentStore::StmtNum ParentStore::getParent(StmtNum child) {
    return parentStore.getKey(child);
}

ParentStore::StmtSet ParentStore::getParentStar(StmtNum child) {
    return parentStarStore.getKeys(child);
}

bool ParentStore::containParentRelation(StmtNum parent, StmtNum child) {
    return parentStore.containsKeyValuePair(parent, child);
}

bool ParentStore::containParentStarRelation(StmtNum parent, StmtNum child) {
    return parentStarStore.containsKeyValuePair(parent, child);
}

bool ParentStore::containParentRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return parentStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return parentStore.containsValue(std::stoi(secondArg.str));
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return parentStore.containsKey(std::stoi(firstArg.str));
    }

    return parentStore.containsKeyValuePair(std::stoi(firstArg.str), std::stoi(secondArg.str));
}

bool ParentStore::containParentStarRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return parentStarStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return parentStarStore.containsValue(std::stoi(secondArg.str));
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return parentStarStore.containsKey(std::stoi(firstArg.str));
    }

    return parentStarStore.containsKeyValuePair(std::stoi(firstArg.str), std::stoi(secondArg.str));
}