#include "CallSemantics.h"

#include <memory>

#include "SP/AST/CallNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/DesignExtraction/Relationship/Util/Helper.h"
#include "SP/Parser/ParserException.h"

using std::unordered_map;
using std::unordered_set;
/**
 */
void CallSemantics::validate(ASTNodePtr_VIEWONLY rootNode) const {
    std::shared_ptr<const ProgramNode> programNode = std::static_pointer_cast<const ProgramNode>(rootNode);

    // [1] Check that all calls are valid (procedure being called exists)
    unordered_set<string> allProcedureNames{};
    for (const auto& p : programNode->getProcedures()) {
        allProcedureNames.insert(p->getName());
    }
    for (const auto& node : programNode->breadthFirstTraversal()) {
        if (node->getType() == NodeType::CALL) {
            auto callNode = std::static_pointer_cast<const CallNode>(node);
            const string procedureCalled = callNode->getProcedureName();
            if (allProcedureNames.find(procedureCalled) == allProcedureNames.end()) {
                throw ParserException("Called Procedure does not exist");
            }
        }
    }

    // [2] Check that there is no cyclical calls
    // Example of cyclical call: A calls B which calls A
    // BFS/DFS will potentially be much faster O(V+E) compared to O(V^3)
    auto directProcedureSubscribersOfProcedure = getProceduresCallingProcedure(programNode);
    unordered_map<string, unordered_set<string>> procedureCallersOfProcedure =
        Helper::getTransitiveClosure(directProcedureSubscribersOfProcedure);

    for (const auto& p : procedureCallersOfProcedure) {
        string procName = p.first;
        auto callingProcedures = p.second;
        if (callingProcedures.find(procName) != callingProcedures.end()) {
            throw ParserException("No Cyclical Calls of Procedure Allowed: " + procName);
        }
    }
}

// direct call
unordered_map<string, unordered_set<string>>
CallSemantics::getProceduresCallingProcedure(const std::shared_ptr<const ProgramNode>& programNode) {
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
