#include "ModifiesRelationshipExtractor.h"

#include <vector>

#include "SP/AST/StmtListNode.h"
#include "SP/DesignExtraction/Relationship/Util/Helper.h"
#include "SP/DesignExtraction/Relationship/Util/SubscriberHelper.h"

/**
 * Extracts out Modifies(stmt, var) and Modifies(procedure, var) relationship
 *
 * New modifies relationship may affect upper parents & callers
 * Therefore main (recursive) function `processStmtList()` must take in that param
 *
 * PREPROCESS: each call node to know which procedure it calls
 * MAIN:
 * - processStmtList(highest stmt list)
 * - traverse nodes in subtree and recursively call `processStmtList()` if required
 * - for relevant nodes store modifies relationship for stmts and procedures
 *
 * @param rootNode
 */
void ModifiesRelationshipExtractor::extractRelationship(const ASTNodePtr& rootNode) {
    std::shared_ptr<ProgramNode> programNode = std::static_pointer_cast<ProgramNode>(rootNode);

    // PRE-PROCESS all call nodes
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
ModifiesRelationshipExtractor::getProceduresCallingProcedure(const std::shared_ptr<ProgramNode>& programNode) {
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

void ModifiesRelationshipExtractor::processProcedure(const std::shared_ptr<ProcedureNode>& procedureNode,
                                                     const unordered_set<int>& stmtSubscribersOfProcedure,
                                                     const unordered_set<string>& procedureSubscribersOfProcedure) {
    auto procedureName = procedureNode->getName();
    auto stmtList = procedureNode->getStmtList();

    unordered_set<string> procedureSubscribersOfStmtList{procedureSubscribersOfProcedure};
    procedureSubscribersOfStmtList.insert(procedureName);

    processStmtList(stmtList, stmtSubscribersOfProcedure, procedureSubscribersOfStmtList);
}

void ModifiesRelationshipExtractor::processStmtList(const std::shared_ptr<StmtListNode>& stmtListNode,
                                                    const unordered_set<int>& stmtSubscribersOfStmtList,
                                                    const unordered_set<string>& procedureSubscribersOfStmtList) {
    for (const auto& stmt : stmtListNode->getSortedStmts()) {
        switch (stmt->getType()) {
        case NodeType::ASSIGN: {
            auto assignNode = std::static_pointer_cast<const AssignNode>(stmt);
            auto stmtNum = assignNode->getStmtNum();
            auto vars = Modified::varNames(assignNode);

            addModifiedVars(stmtNum, vars);
            addModifiedVars(stmtSubscribersOfStmtList, vars);
            addModifiedVarsForProcedure(procedureSubscribersOfStmtList, vars);
            break;
        }
        case NodeType::READ: {
            auto readNode = std::static_pointer_cast<const ReadNode>(stmt);
            auto stmtNum = readNode->getStmtNum();
            auto vars = Modified::varNames(readNode);

            addModifiedVars(stmtNum, vars);
            addModifiedVars(stmtSubscribersOfStmtList, vars);
            addModifiedVarsForProcedure(procedureSubscribersOfStmtList, vars);
            break;
        }
        case NodeType::IF_THEN_ELSE: {
            auto ifNode = std::static_pointer_cast<const IfThenElseNode>(stmt);
            auto ifStmtNum = ifNode->getStmtNum();

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

void ModifiesRelationshipExtractor::flush() {
    // stmt
    pkbAdapter->setStatementModifiesRelationship(modifiedVarsInStatement);
    modifiedVarsInStatement = {};

    // procedures
    pkbAdapter->setProcedureModifiesRelationship(modifiedVarsInProcedure);
    modifiedVarsInProcedure = {};
}

void ModifiesRelationshipExtractor::addModifiedVars(int stmt, unordered_set<string> vars) {
    modifiedVarsInStatement[stmt].insert(vars.begin(), vars.end());
}

void ModifiesRelationshipExtractor::addModifiedVars(const unordered_set<int>& stmts, unordered_set<string> vars) {
    for (int s : stmts) {
        addModifiedVars(s, vars);
    }
}

void ModifiesRelationshipExtractor::addModifiedVarsForProcedure(const string& procName, unordered_set<string> vars) {
    modifiedVarsInProcedure[procName].insert(vars.begin(), vars.end());
}

void ModifiesRelationshipExtractor::addModifiedVarsForProcedure(const unordered_set<string>& procNames,
                                                                unordered_set<std::string> vars) {
    for (std::string name : procNames) {
        modifiedVarsInProcedure[name].insert(vars.begin(), vars.end());
    }
}

namespace Modified {
    std::unordered_set<string> varNames(const std::shared_ptr<const AssignNode>& assignNode) {
        return Helper::getVarNamesInSubtree(assignNode->getVarNode());
    }

    std::unordered_set<string> varNames(const std::shared_ptr<const ReadNode>& readNode) {
        return {readNode->getVarNode()->getName()};
    }
}
