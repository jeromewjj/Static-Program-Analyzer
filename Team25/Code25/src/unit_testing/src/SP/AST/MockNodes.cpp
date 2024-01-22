
#include "MockNodes.h"

#include <memory>

#include "SP/AST/AssignNode.h"
#include "SP/AST/BinaryExpressionNode.h"
#include "SP/AST/ConstantNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/PrintNode.h"
#include "SP/AST/ReadNode.h"
#include "SP/AST/WhileThenNode.h"

std::shared_ptr<AssignNode> MockAssignments::mock0() {
    auto assignNode = std::make_shared<AssignNode>("x", 1);
    auto expr = std::make_shared<BinaryExpressionNode>("+", std::make_shared<ConstantNode>("1"),
                                                       std::make_shared<ConstantNode>("2"));
    assignNode->addChild(expr);
    return assignNode;
}

// while (x < 0) { read x; }
std::shared_ptr<WhileThenNode> MockWhile::mock0() {
    auto while1_stmtNum = 1;
    auto while1_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("x"),
                                                                   std::make_shared<ConstantNode>("0"));
    auto while1_stmtList =
        std::make_shared<StmtListNode>(StmtListNode({std::make_shared<ReadNode>("x", MOCK_STMT_NUM)}));
    const auto condVars = unordered_set<string>{"x"};
    const auto node = std::make_shared<WhileThenNode>(while1_condition, while1_stmtList, while1_stmtNum);
    return node;
}

// if (y < 0) then { print y; } else { print x; }
std::shared_ptr<IfThenElseNode> MockIf::mock0() {
    auto if1_stmtNum = 1;
    auto if1_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("y"),
                                                                std::make_shared<ConstantNode>("0"));
    auto if1_then = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("y", MOCK_STMT_NUM)}));
    auto if1_else = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("x", MOCK_STMT_NUM)}));
    const auto condVars = unordered_set<string>{"y"};
    const auto node = std::make_shared<IfThenElseNode>(if1_condition, if1_then, if1_else, if1_stmtNum);
    return node;
}
