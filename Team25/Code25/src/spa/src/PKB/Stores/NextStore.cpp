#include "NextStore.h"

void NextStore::setNextRelationships(const NextSet& nextSet) {
    // Insert Next relationship into Next Store
    for (const auto& nextPair : nextSet) {
        // followPair.first is Previous and followPair.second is Next
        nextStore.insert(nextPair.first, nextPair.second);
    }

    this->nextPairSet = nextSet;
}

NextStore::StmtSet NextStore::getNext(const NextStore::StmtNum stmtNum) {
    return this->nextStore.getValues(stmtNum);
}

bool NextStore::containNextRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return nextStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return nextStore.containsValue(std::stoi(secondArg.str));
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return nextStore.containsKey(std::stoi(firstArg.str));
    }

    return nextStore.containsKeyValuePair(std::stoi(firstArg.str), std::stoi(secondArg.str));
}

bool NextStore::containNextStarRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return nextStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return nextStore.containsValue(std::stoi(secondArg.str));
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return nextStore.containsKey(std::stoi(firstArg.str));
    }

    if (!this->isStarGenerated) {
        generateNextStarRelationship();
    }

    return nextStarStore.containsKeyValuePair(std::stoi(firstArg.str), std::stoi(secondArg.str));
}

void NextStore::generateNextStarRelationship() {
    if (!this->isStarGenerated) {
        NextSet nextStarSet = StarRelationshipUtil<StmtNum>::GenerateStarRelations(this->nextPairSet);
        for (const auto& nextPair : nextStarSet) {
            // followPair.first is Previous and followPair.second is Next
            nextStarStore.insert(nextPair.first, nextPair.second);
        }
        this->isStarGenerated = true;
    }
}

void NextStore::clearNextStarStore() {
    if (this->isStarGenerated) {
        this->nextStarStore = BiMapManyToMany<StmtNum, StmtNum>();
        this->isStarGenerated = false;
    }
}