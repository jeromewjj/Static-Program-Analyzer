#include "FollowsStore.h"

void FollowsStore::setFollowsRelationships(const FollowsSet& followSet) {

    // Insert Follow relationship into Follow Store
    for (const auto& followPair : followSet) {
        // followPair.first is Followee and followPair.second is Follower
        followsStore.insert(followPair.first, followPair.second);
    }

    FollowsSet followStarSet = StarRelationshipUtil<StmtNum>::GenerateStarRelations(followSet);

    // Insert Follow star relationship into Follow Star Store
    for (const auto& followPair : followStarSet) {
        // followPair.first is Followee and followPair.second is Follower
        followsStarStore.insert(followPair.first, followPair.second);
    }
}

FollowsStore::StmtNum FollowsStore::getFollower(StmtNum followee) {
    return followsStore.getValue(followee);
}

FollowsStore::StmtSet FollowsStore::getFollowerStars(StmtNum followee) {
    return followsStarStore.getValues(followee);
}

FollowsStore::StmtNum FollowsStore::getFollowee(StmtNum follower) {
    return followsStore.getKey(follower);
}

FollowsStore::StmtSet FollowsStore::getFolloweeStars(StmtNum follower) {
    return followsStarStore.getKeys(follower);
}

bool FollowsStore::containFollowsRelation(StmtNum followee, StmtNum follower) {
    return followsStore.containsKeyValuePair(followee, follower);
}

bool FollowsStore::containFollowsStarRelation(StmtNum followee, StmtNum follower) {
    return followsStarStore.containsKeyValuePair(followee, follower);
}

bool FollowsStore::containFollowsRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return followsStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return followsStore.containsValue(std::stoi(secondArg.str));
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return followsStore.containsKey(std::stoi(firstArg.str));
    }

    return followsStore.containsKeyValuePair(std::stoi(firstArg.str), std::stoi(secondArg.str));
}

bool FollowsStore::containFollowsStarRelation(Argument firstArg, Argument secondArg) {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return followsStarStore.length() > 0;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        return followsStarStore.containsValue(std::stoi(secondArg.str));
    }

    if (secondArg.type == ArgType::WILDCARD) {
        return followsStarStore.containsKey(std::stoi(firstArg.str));
    }

    return followsStarStore.containsKeyValuePair(std::stoi(firstArg.str), std::stoi(secondArg.str));
}