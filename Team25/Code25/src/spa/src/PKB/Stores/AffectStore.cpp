#include "AffectStore.h"

void AffectStore::setAffectRelationships(const AffectSet& affectSet) {
    // Insert Affect relationship into Affect Store
    for (const auto& affectPair : affectSet) {
        // followPair.first is Previous and followPair.second is Next
        affectStore.insert(affectPair.first, affectPair.second);
    }

    this->isAffectGenerated = true;
}

bool AffectStore::containAffectRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return affectStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return affectStore.containsValue(std::stoi(secondArg.str));
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return affectStore.containsKey(std::stoi(firstArg.str));
    }

    return affectStore.containsKeyValuePair(std::stoi(firstArg.str), std::stoi(secondArg.str));
}

void AffectStore::clearAffectStore() {
    if (this->isAffectGenerated) {
        this->affectStore = BiMapManyToMany<StmtNum, StmtNum>();
        this->isAffectGenerated = false;
    }
}

bool AffectStore::checkAffectGenerated() {
    return this->isAffectGenerated;
}