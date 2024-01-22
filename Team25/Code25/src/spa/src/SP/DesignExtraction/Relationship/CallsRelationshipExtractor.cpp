#include "CallsRelationshipExtractor.h"

void CallsRelationshipExtractor::extractRelationship(const ASTNodePtr& rootNode) {
    std::shared_ptr<ProgramNode> programNode = std::static_pointer_cast<ProgramNode>(rootNode);
    vector<std::shared_ptr<ProcedureNode>> proceduresNodes = programNode->getProcedures();

    for (const auto& procedureNode : proceduresNodes) {
        const string caller = procedureNode->getName();
        std::vector<ASTNodePtr_VIEWONLY> nodes = procedureNode->breadthFirstTraversal();
        for (const auto& node : nodes) {
            if (node->getType() == NodeType::CALL) {
                auto callNode = std::static_pointer_cast<const CallNode>(node);
                const string callee = callNode->getProcedureName();
                callsSet->insert({caller, callee});
            }
        }
    }
}

void CallsRelationshipExtractor::flush() {
    pkbAdapter->setProcedureCallsRelationship(callsSet);
    callsSet->clear();
}
