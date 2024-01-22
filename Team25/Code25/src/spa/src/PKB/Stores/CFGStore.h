#pragma once

#include <algorithm>
#include <stack>
#include <vector>

#include "PKB/Mappings/BiMapManyToMany.h"
#include "PKB/Mappings/BiMapOneToMany.h"
#include "PKB/Mappings/BiMapOneToOne.h"
#include "PKB/Types/CFGType.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/RelationshipType.h"

class CFGStore {
public:
    using CFGBlockSet = std::unordered_set<CFGBlock>;
    using StmtNum = EntityTypes::STATEMENT_NUMBER;
    using NextSet = std::unordered_set<RelationshipTypes::NEXT_PAIR>;

    /**
     * Sets CFG node into the store
     *
     * @param cfgBlocks - The set of CFG Blocks to be store
     */
    void setCfg(const CFGBlockSet& cfgBlocks);

    /**
     * Generate Next Relationship from the CFG store
     *
     * @return a set of Next Relationship Pair
     */
    NextSet generateNextRelation();

private:
    // Block id to Stmt Number
    BiMapOneToMany<int, StmtNum> stmtStore;
    // Parent Block id to Child Block id
    BiMapManyToMany<int, int> blockStore;
    // Block id to Block Type
    BiMapOneToMany<CFGBlockType, int> blockTypeStore;
    // Procedure Name to Block id
    BiMapOneToMany<std::string, int> procStore;
    // Procedure Name To Start Block id
    BiMapOneToOne<std::string, int> startBlockStore;
    // Block id to start stmt number of the block
    std::unordered_map<int, int> startStmtStore;
    // Block id to end stmt number of the block
    std::unordered_map<int, int> endStmtStore;

    // Generate the "Next" relation within a cfg block
    void generateNextRelationFromBlock(NextSet& nextSet);
    // Generate the "Next" relation between cfg block of a procedure
    void generateNextRelationFromProcedure(NextSet& nextSet);
    // Get actual cfg block
    std::unordered_set<int> getChildBlocks(int blockId);
};
