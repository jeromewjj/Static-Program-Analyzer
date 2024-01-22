#include "SubscriberHelper.h"

#include "SP/AST/CallNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/WhileThenNode.h"

using std::pair;
using std::queue;
using std::string;
using std::unordered_map;
using std::unordered_set;

namespace Subscriber_Helper {
    unordered_map<STMT_NUM, unordered_set<PROCEDURE_NAME>> getProcedureSubscriptionsOfStmts(
        const std::shared_ptr<ProgramNode>& programNode,
        const unordered_map<string, unordered_set<string>>& procedureSubscriptionsOfProcedure) {

        unordered_map<int, unordered_set<string>> proceduresSubscriptionsOfCallStmts{};

        const auto directlySubscribedStmtsOfProcedure =
            Subscriber_Helper::getDirectStmtSubscribersOfProcedure(programNode);
        for (const auto& p : directlySubscribedStmtsOfProcedure) {
            const string procName = p.first;
            const auto stmts = p.second;

            const bool hasProcedureSubscriptions =
                (procedureSubscriptionsOfProcedure.find(procName) != procedureSubscriptionsOfProcedure.end());

            for (const int& s : stmts) {
                // 1) subscribed to procedure being called
                proceduresSubscriptionsOfCallStmts[s].insert(procName);
                // 2) subscribed to all procedure subscriptions of the procedure being called
                if (hasProcedureSubscriptions) {
                    auto x = procedureSubscriptionsOfProcedure.at(procName);
                    proceduresSubscriptionsOfCallStmts[s].insert(x.begin(), x.end());
                }
            }
        }
        return proceduresSubscriptionsOfCallStmts;
    }

    StmtSubscriberMap getDirectStmtSubscribersOfProcedure(const std::shared_ptr<ProgramNode>& programNode) {
        std::shared_ptr<StmtSubscriberMap> directStmtSubscribersOfProcedure = std::make_shared<StmtSubscriberMap>();
        std::shared_ptr<AncestorStack> ancestors = std::make_shared<AncestorStack>();

        for (const auto& procNode : programNode->getProcedures()) {
            const std::string procName = procNode->getName();
            dfsUpdateSubscribers(procNode, directStmtSubscribersOfProcedure, ancestors);
        }

        return *directStmtSubscribersOfProcedure;
    }

    void dfsUpdateSubscribers(const std::shared_ptr<const ASTNode>& node,
                              const std::shared_ptr<StmtSubscriberMap> directStmtSubscribersOfProcedure,
                              const std::shared_ptr<AncestorStack>& ancestors) {
        const NodeType nodeType = node->getType();
        bool isContainerStmt = nodeType == NodeType::IF_THEN_ELSE || nodeType == NodeType::WHILE_THEN;
        int containerStmtNum = 0;
        if (isContainerStmt) {
            switch (nodeType) {
            case (NodeType::IF_THEN_ELSE):
                containerStmtNum = std::static_pointer_cast<const IfThenElseNode>(node)->getStmtNum();
                break;
            case (NodeType::WHILE_THEN):
                containerStmtNum = std::static_pointer_cast<const WhileThenNode>(node)->getStmtNum();
                break;
            default:
                throw std::runtime_error("Shouldn't be able to run here");
            }

            ancestors->insert(containerStmtNum);
        };

        if (node->getType() == NodeType::CALL) {
            auto callNode = std::static_pointer_cast<const CallNode>(node);
            const std::string procCalled = callNode->getProcedureName();
            const int callStmtNum = callNode->getStmtNum();

            // Add the procCalled and its subscribers
            (*directStmtSubscribersOfProcedure)[procCalled].insert(callStmtNum);

            // Include statement numbers of container nodes
            (*directStmtSubscribersOfProcedure)[procCalled].insert(ancestors->begin(), ancestors->end());
        }

        // Recursively visit children
        for (const auto& child : node->getChildren()) {
            dfsUpdateSubscribers(child, directStmtSubscribersOfProcedure, ancestors);
        }

        // cleanUp
        if (isContainerStmt) {
            assert(containerStmtNum != 0); // assert it has been assigned
            ancestors->erase(containerStmtNum);
        }
    }
}
