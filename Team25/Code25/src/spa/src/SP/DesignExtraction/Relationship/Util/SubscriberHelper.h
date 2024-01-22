#pragma once
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "SP/AST/ASTNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/AST/VariableNode.h"

namespace Subscriber_Helper {
    using PROCEDURE_NAME = string;
    using STMT_NUM = int;
    using AncestorStack = unordered_set<STMT_NUM>;
    using StmtSubscriberMap = std::unordered_map<PROCEDURE_NAME, std::unordered_set<STMT_NUM>>;

    std::unordered_map<STMT_NUM, unordered_set<PROCEDURE_NAME>> getProcedureSubscriptionsOfStmts(
        const std::shared_ptr<ProgramNode>& programNode,
        const std::unordered_map<PROCEDURE_NAME, unordered_set<PROCEDURE_NAME>>& procedureSubscriptionsOfProcedure);
    /**
     * directly subscribed statements
     * because it only considers each callingStatement and it's parent container statements
     *
     * if stmt S calls procedure of name P,
     * P: {S} UNION { ParentContainerStmts_of_S }
     *
     * NO CONSIDERATION of transitive relationships such as if P calls another procedure P1
     *
     *
     * @param rootNode
     * @return directly subscribed statements of a procedure
     */
    std::unordered_map<PROCEDURE_NAME, unordered_set<STMT_NUM>>
    getDirectStmtSubscribersOfProcedure(const std::shared_ptr<ProgramNode>& programNode);
    void dfsUpdateSubscribers(const std::shared_ptr<const ASTNode>& node,
                              const std::shared_ptr<StmtSubscriberMap> directStmtSubscribersOfProcedure,
                              const std::shared_ptr<AncestorStack>& ancestors);
}