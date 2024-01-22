#include "UsesRelationshipExtractor.h"

#include <vector>

#include "SP/AST/StmtListNode.h"
#include "SP/DesignExtraction/Relationship/Util/Helper.h"
#include "SP/DesignExtraction/Relationship/Util/SubscriberHelper.h"

/**
 * Extracts out Uses(stmt, var) and Uses(procedure, var) relationship
 *
 * New uses relationship may affect upper parents & callers
 * Therefore main (recursive) function `processStmtList()` must take in that param
 *
 * PREPROCESS: each call node to know which procedure it calls
 * MAIN:
 * - processStmtList(highest stmt list)
 * - traverse nodes in subtree and recursively call `processStmtList()` if required
 * - for relevant nodes store Uses relationship for stmts and procedures
 *
 * @param rootNode
 */
void UsesRelationshipExtractor::extractRelationship(const ASTNodePtr& rootNode) {
    std::shared_ptr<ProgramNode> programNode = std::static_pointer_cast<ProgramNode>(rootNode);

    // PRE-PROCESS
    // 1) get all procedure subscribers (to changes within each procedure)
    auto directProcedureSubscribersOfProcedure = getProceduresCallingProcedure(programNode);
    unordered_map<string, unordered_set<string>> procedureSubscribersOfProcedure =
        Helper::getTransitiveClosure(directProcedureSubscribersOfProcedure);

    // 2) get all stmt subscribers (to changes within each procedure)
    const auto procedureSubscriptionsOfProcedure = Helper::reverseMap(procedureSubscribersOfProcedure);
    auto procedureSubscriptionsOfStmt =
        Subscriber_Helper::getProcedureSubscriptionsOfStmts(programNode, procedureSubscriptionsOfProcedure);
    unordered_map<string, unordered_set<int>> stmtSubscribersOfProcedure =
        Helper::reverseMap(procedureSubscriptionsOfStmt);

    // PROCESS
    for (const auto& procNode : programNode->getProcedures()) {
        processProcedure(procNode, stmtSubscribersOfProcedure[procNode->getName()],
                         procedureSubscribersOfProcedure[procNode->getName()]);
    }
}

// direct call
unordered_map<string, unordered_set<string>>
UsesRelationshipExtractor::getProceduresCallingProcedure(const std::shared_ptr<ProgramNode>& programNode) {
    unordered_map<string, unordered_set<string>> proceduresCallingProcedure{};
    for (const auto& procNode : programNode->getProcedures()) {
        const string containerProcedure = procNode->getName();
        for (const auto& node : procNode->breadthFirstTraversal()) {
            if (node->getType() == NodeType::CALL) {
                auto callNode = std::static_pointer_cast<const CallNode>(node);
                const string procedureCalled = callNode->getProcedureName();
                proceduresCallingProcedure[procedureCalled].insert(containerProcedure);
            }
        }
    }
    return proceduresCallingProcedure;
}

void UsesRelationshipExtractor::processProcedure(const std::shared_ptr<ProcedureNode>& procedureNode,
                                                 const unordered_set<int>& stmtSubscribersOfProcedure,
                                                 const unordered_set<string>& procedureSubscribersOfProcedure) {
    auto procedureName = procedureNode->getName();
    auto stmtList = procedureNode->getStmtList();

    unordered_set<string> procedureSubscribersOfStmtList{procedureSubscribersOfProcedure};
    procedureSubscribersOfStmtList.insert(procedureName);

    processStmtList(stmtList, stmtSubscribersOfProcedure, procedureSubscribersOfStmtList);
}

void UsesRelationshipExtractor::processStmtList(const std::shared_ptr<StmtListNode>& stmtListNode,
                                                const unordered_set<int>& stmtSubscribersOfStmtList,
                                                const unordered_set<string>& procedureSubscribersOfStmtList) {
    for (const auto& stmt : stmtListNode->getSortedStmts()) {
        switch (stmt->getType()) {
        case NodeType::ASSIGN: {
            auto assignNode = std::static_pointer_cast<const AssignNode>(stmt);
            auto stmtNum = assignNode->getStmtNum();
            auto usedVars = Used::varNames(assignNode);

            addUsedVars(stmtNum, usedVars);
            addUsedVars(stmtSubscribersOfStmtList, usedVars);
            addUsedVarsForProcedure(procedureSubscribersOfStmtList, usedVars);
            break;
        }
        case NodeType::PRINT: {
            auto printNode = std::static_pointer_cast<const PrintNode>(stmt);
            auto stmtNum = printNode->getStmtNum();
            auto usedVars = Used::varNames(printNode);

            addUsedVars(stmtNum, usedVars);
            addUsedVars(stmtSubscribersOfStmtList, usedVars);
            addUsedVarsForProcedure(procedureSubscribersOfStmtList, usedVars);
            break;
        }
        case NodeType::IF_THEN_ELSE: {
            auto ifNode = std::static_pointer_cast<const IfThenElseNode>(stmt);
            auto ifStmtNum = ifNode->getStmtNum();
            auto usedVarsInCondition = Helper::getVarNamesInSubtree(ifNode->getConditionNode());

            addUsedVars(ifStmtNum, usedVarsInCondition);
            addUsedVars(stmtSubscribersOfStmtList, usedVarsInCondition);
            addUsedVarsForProcedure(procedureSubscribersOfStmtList, usedVarsInCondition);

            // process then & else stmtLists
            unordered_set<int> newStmtSubscribersOfStmtList{stmtSubscribersOfStmtList};
            newStmtSubscribersOfStmtList.insert(ifStmtNum);

            processStmtList(ifNode->getThenNode(), newStmtSubscribersOfStmtList, procedureSubscribersOfStmtList);
            processStmtList(ifNode->getElseNode(), newStmtSubscribersOfStmtList, procedureSubscribersOfStmtList);
            break;
        }
        case NodeType::WHILE_THEN: {
            auto whileNode = std::static_pointer_cast<const WhileThenNode>(stmt);
            auto whileStmtNum = whileNode->getStmtNum();
            auto usedVarsInCondition = Helper::getVarNamesInSubtree(whileNode->getConditionNode());

            addUsedVars(whileStmtNum, usedVarsInCondition);
            addUsedVars(stmtSubscribersOfStmtList, usedVarsInCondition);
            addUsedVarsForProcedure(procedureSubscribersOfStmtList, usedVarsInCondition);

            // process then stmtLists
            unordered_set<int> newStmtSubscribersOfStmtList(stmtSubscribersOfStmtList);
            newStmtSubscribersOfStmtList.insert(whileStmtNum);

            processStmtList(whileNode->getThenNode(), newStmtSubscribersOfStmtList, procedureSubscribersOfStmtList);
            break;
        }
        default:
            break;
        }
    }
}

void UsesRelationshipExtractor::flush() {
    // stmt
    pkbAdapter->setStatementUsesRelationship(usedVarsInStatement);
    usedVarsInStatement = {};

    // procedures
    pkbAdapter->setProcedureUsesRelationship(usedVarsInProcedure);
    usedVarsInProcedure = {};
}

void UsesRelationshipExtractor::addUsedVars(int stmt, unordered_set<string> vars) {
    usedVarsInStatement[stmt].insert(vars.begin(), vars.end());
}
void UsesRelationshipExtractor::addUsedVars(const unordered_set<int>& stmts, unordered_set<string> vars) {
    for (int stmt : stmts) {
        addUsedVars(stmt, vars);
    }
}
void UsesRelationshipExtractor::addUsedVarsForProcedure(const string& procName, unordered_set<string> vars) {
    usedVarsInProcedure[procName].insert(vars.begin(), vars.end());
}

void UsesRelationshipExtractor::addUsedVarsForProcedure(const unordered_set<string>& procNames,
                                                        unordered_set<string> vars) {
    for (string name : procNames) {
        usedVarsInProcedure[name].insert(vars.begin(), vars.end());
    }
}

namespace Used {
    std::unordered_set<string> varNames(const std::shared_ptr<const AssignNode>& assignNode) {
        return Helper::getVarNamesInSubtree(assignNode->getAssignedExpressionNode());
    }

    std::unordered_set<string> varNames(const std::shared_ptr<const PrintNode>& printNode) {
        return {printNode->getVarNode()->getName()};
    }
}
