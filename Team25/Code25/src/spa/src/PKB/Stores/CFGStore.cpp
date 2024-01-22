#include "CFGStore.h"

void CFGStore::setCfg(const CFGBlockSet& cfgBlocks) {
    for (const auto& cfgBlock : cfgBlocks) {
        this->blockTypeStore.insert(cfgBlock.type, cfgBlock.id);
        this->procStore.insert(cfgBlock.proc, cfgBlock.id);

        if (cfgBlock.type == CFGBlockType::START_PROC) {
            this->startBlockStore.insert(cfgBlock.proc, cfgBlock.id);
        }

        for (const auto stmt : cfgBlock.stmtSet) {
            this->stmtStore.insert(cfgBlock.id, stmt);
        }

        for (const auto blockId : cfgBlock.nextSet) {
            this->blockStore.insert(cfgBlock.id, blockId);
        }
    }
}

CFGStore::NextSet CFGStore::generateNextRelation() {
    NextSet nextSet;

    // Generate the "Next" relation within a cfg block
    generateNextRelationFromBlock(nextSet);

    // Generate the "Next" relation between cfg block of a procedure
    generateNextRelationFromProcedure(nextSet);

    return nextSet;
}

void CFGStore::generateNextRelationFromBlock(NextSet& nextSet) {
    std::unordered_set<int> blocks = this->blockTypeStore.getAllValues();
    for (const auto& block : blocks) {
        std::unordered_set<int> stmtSet = this->stmtStore.getValues(block);

        if (stmtSet.empty()) {
            continue;
        }

        std::vector<int> stmtList(stmtSet.begin(), stmtSet.end());
        std::sort(stmtList.begin(), stmtList.end());

        for (size_t i = 0; i < stmtList.size() - 1; ++i) {
            nextSet.insert({stmtList[i], stmtList[i + 1]});
        }

        this->startStmtStore[block] = stmtList.front();
        this->endStmtStore[block] = stmtList.back();
    }
}

void CFGStore::generateNextRelationFromProcedure(NextSet& nextSet) {
    std::unordered_set<std::string> procSet = this->procStore.getAllKeys();
    std::unordered_set<int> visited;
    std::vector<int> stack;

    for (const auto& proc : procSet) {
        int startBlock = this->startBlockStore.getValue(proc);
        stack.emplace_back(startBlock);

        while (!stack.empty()) {
            int block = stack[0];
            stack.erase(stack.begin());

            if (visited.find(block) != visited.end()) {
                continue;
            }

            visited.insert(block);
            std::unordered_set<int> childBlocks = getChildBlocks(block);

            for (const int childBlockId : childBlocks) {
                int blockEndStmt = endStmtStore[block];
                if (this->startStmtStore.find(childBlockId) == this->startStmtStore.end()) {
                    continue;
                }
                int childBlockStartStmt = startStmtStore[childBlockId];
                nextSet.insert({blockEndStmt, childBlockStartStmt});

                if (visited.find(childBlockId) == visited.end()) {
                    stack.emplace_back(childBlockId);
                }
            }
        }
    }
}

std::unordered_set<int> CFGStore::getChildBlocks(int blockId) {
    std::unordered_set<int> result;
    std::stack<int> toVisit;

    toVisit.push(blockId);

    while (!toVisit.empty()) {
        int currentBlock = toVisit.top();
        toVisit.pop();

        std::unordered_set<int> childBlocks = this->blockStore.getValues(currentBlock);

        for (int childBlock : childBlocks) {
            if (this->blockTypeStore.getKey(childBlock) != CFGBlockType::DUMMY) {
                result.insert(childBlock);
            }
            else {
                toVisit.push(childBlock);
            }
        }
    }

    return result;
}