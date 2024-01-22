#include "MockASTs.h"

#include "SP/AST/AssignNode.h"
#include "SP/AST/BinaryExpressionNode.h"
#include "SP/AST/CallNode.h"
#include "SP/AST/ConstantNode.h"
#include "SP/AST/Expression.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/PrintNode.h"
#include "SP/AST/ProcedureNode.h"
#include "SP/AST/ReadNode.h"
#include "SP/AST/StmtListNode.h"
#include "SP/AST/VariableNode.h"
#include "SP/AST/WhileThenNode.h"

// -------------- CODE
/*
// Procedure p {}
*/
// -------------- TREE
/*
// main
// └── p
//     └── StmtList
*/
std::shared_ptr<ProgramNode> MockASTs::mock0() {
    // BASE_TEMPLATE
    // (links) main_program -> procedure -> procStmtList
    const std::string DEFAULT_PROGRAM_NAME = "main";
    auto programNode = std::make_shared<ProgramNode>(DEFAULT_PROGRAM_NAME);
    auto proc = std::make_shared<ProcedureNode>("p");
    auto procStmtList = proc->getStmtList();
    programNode->addChild(proc);
    // --------------------- //
    return programNode;
}

// -------------- CODE
/*
// Procedure p {
//   x = 2;
//   read y;
//   print x;
// }
*/
// -------------- TREE
/*
// main
// └── p
//     └── StmtList
//         ├── Assign
//         │   ├── Variable (x)
//         │   └── Constant (2)
//         ├── Read
//         │   └── Variable (y)
//         └── Print
//             └── Variable (x)
*/
std::shared_ptr<ProgramNode> MockASTs::mock1() {
    int stmtNum = 1;
    // BASE_TEMPLATE
    // (links) main_program -> procedure -> procStmtList
    const std::string DEFAULT_PROGRAM_NAME = "main";
    auto programNode = std::make_shared<ProgramNode>(DEFAULT_PROGRAM_NAME);
    auto proc = std::make_shared<ProcedureNode>("p");
    auto procStmtList = proc->getStmtList();
    programNode->addChild(proc);
    // --------------------- //

    // >>> proc_STMTLIST [START] <<<
    auto assignNode = std::make_shared<AssignNode>("x", stmtNum++);
    auto const2 = std::make_shared<ConstantNode>("2");
    assignNode->addChild(const2);
    auto readNode = std::make_shared<ReadNode>("y", stmtNum++);
    auto printNode = std::make_shared<PrintNode>("x", stmtNum++);

    procStmtList->addChild(assignNode);
    procStmtList->addChild(readNode);
    procStmtList->addChild(printNode);
    // >>> proc_STMTLIST [END] <<<

    return programNode;
}

// -------------- CODE
/*
// Procedure p {
//   read x;
//   while (x < 0) { read x; }
//
//   read y;
//   if (y < 0) {
//     print y;
//   } else {
//     print x;
//   }
// }
*/
// -------------- TREE
/*
// main
// └── p
//     └── StmtList
//         ├── Read
//         │   └── Variable (x)
//         ├── WhileThen
//         │   ├── BinaryExpression (<)
//         │   │   ├── Variable (x)
//         │   │   └── Constant (0)
//         │   └── StmtList
//         │       └── Read
//         │           └── Variable (x)
//         │
//         ├── Read
//         │   └── Variable (y)
//         └── IfThenElse
//             ├── BinaryExpr (<)
//             │   ├── Variable (y)
//             │   └── Constant (0)
//             ├── StmtList
//             │   └── Print
//             │       └── Variable (y)
//             └── StmtList
//                 └── Print
//                     └── Variable (x)
*/
std::shared_ptr<ProgramNode> MockASTs::mock2() {
    int stmtNum = 1;

    // BASE_TEMPLATE [START] //
    // (links) main_program -> procedure -> procStmtList
    const std::string DEFAULT_PROGRAM_NAME = "main";
    auto programNode = std::make_shared<ProgramNode>(DEFAULT_PROGRAM_NAME);
    auto proc = std::make_shared<ProcedureNode>("p");
    auto procStmtList = proc->getStmtList();
    programNode->addChild(proc);
    // --------------------- //

    // >>> proc_STMTLIST [START] <<<

    // read x;
    auto readX = std::make_shared<ReadNode>("x", stmtNum++);

    // while (x<0) { ... }
    auto while_stmtNum = stmtNum++;
    auto while_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("x"),
                                                                  std::make_shared<ConstantNode>("0"));
    auto while_stmtList = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<ReadNode>("x", stmtNum++)}));
    auto whileNode = std::make_shared<WhileThenNode>(while_condition, while_stmtList, while_stmtNum);

    // read y;
    auto readY = std::make_shared<ReadNode>("y", stmtNum++);

    // if (y < 0) then {...} else {...}
    auto if_stmtNum = stmtNum++;
    auto if_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("y"),
                                                               std::make_shared<ConstantNode>("0"));
    auto if_then = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("y", stmtNum++)}));
    auto if_else = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("x", stmtNum++)}));
    auto ifNode = std::make_shared<IfThenElseNode>(if_condition, if_then, if_else, if_stmtNum);

    procStmtList->addChild(readX);
    procStmtList->addChild(whileNode);
    procStmtList->addChild(readY);
    procStmtList->addChild(ifNode);
    // >>> proc_STMTLIST [END] <<<

    return programNode;
}

// -------------- CODE
/*
// Procedure p1 {
//   x = 2;
//   read y;
//   call p2
//   print x;
//   call p3;
// }
// Procedure p2 {
//   read y;
// }
// Procedure p3 {
//   call p2;
// }
*/
// -------------- TREE
/*
//    main
//    ├── p1
//    │   └── StmtList
//    │        ├── Assign
//    │        │   ├── Variable (x)
//    │        │   └── Constant (2)
//    │        ├── Read
//    │        │   └── Variable (y)
//    │        ├── Call
//    │        │   └── Procedure (p2)
//    │        ├── Print
//    │        │   └── Variable (x)
//    │        └── Call
//    │            └── Procedure (p3)
//    ├── p2
//    │   └── StmtList
//    │       └── Read
//    │           └── Variable (y)
//    └── p3
//        └── StmtList
//            └── Call
//                └── Procedure (p2)
*/
std::shared_ptr<ProgramNode> MockASTs::mock3() {
    int stmtNum = 1;

    // BASE_TEMPLATE [START]
    const std::string DEFAULT_PROGRAM_NAME = "main";
    auto programNode = std::make_shared<ProgramNode>(DEFAULT_PROGRAM_NAME);
    auto proc1 = std::make_shared<ProcedureNode>("p1");
    auto proc1StmtList = proc1->getStmtList();
    auto proc2 = std::make_shared<ProcedureNode>("p2");
    auto proc2StmtList = proc2->getStmtList();
    auto proc3 = std::make_shared<ProcedureNode>("p3");
    auto proc3StmtList = proc3->getStmtList();

    programNode->addChild(proc1);
    programNode->addChild(proc2);
    programNode->addChild(proc3);
    // BASE_TEMPLATE [END]

    // >>> proc1_STMTLIST [START] <<<

    // x = 2;
    auto assignX = std::make_shared<AssignNode>("x", stmtNum++);
    auto const2 = std::make_shared<ConstantNode>("2");
    assignX->addChild(const2);

    // read y;
    auto readY = std::make_shared<ReadNode>("y", stmtNum++);

    // call p2;
    auto callP2 = std::make_shared<CallNode>("p2", stmtNum++);

    // print x;
    auto printX = std::make_shared<PrintNode>("x", stmtNum++);

    // call p3;
    auto callP3 = std::make_shared<CallNode>("p3", stmtNum++);

    proc1StmtList->addChild(assignX);
    proc1StmtList->addChild(readY);
    proc1StmtList->addChild(callP2);
    proc1StmtList->addChild(printX);
    proc1StmtList->addChild(callP3);
    // >>> proc1_STMTLIST [END] <<<

    // >>> proc2_STMTLIST [START] <<<

    // read y;
    auto readY2 = std::make_shared<ReadNode>("y", stmtNum++);

    proc2StmtList->addChild(readY2);
    // >>> proc2_STMTLIST [END] <<<

    // >>> proc3_STMTLIST [START] <<<

    // call p2;
    auto callP2_3 = std::make_shared<CallNode>("p2", stmtNum++);

    proc3StmtList->addChild(callP2_3);
    // >>> proc3_STMTLIST [END] <<<

    return programNode;
}

// -------------- CODE
/*
// Procedure p {
//1   x = 1 + 2;
//2   y = 3 + x;
//3   z = x + y;
// }
*/
// -------------- TREE
/*
// main
// └── p
//     └── StmtList
//         ├── Assign
//         │   └── Variable (x)
//         │   └── BinaryExpression (+)
//         │       └── Constant (1)
//         │       └── Constant (2)
//         ├── Assign
//         │   └── Variable (y)
//         │   └── BinaryExpression (+)
//         │       └── Constant (3)
//         │       └── Variable (x)
//         └── Assign
//             └── Variable (z)
//             └── BinaryExpression (+)
//                 └── Variable (x)
//                 └── Variable (y)
*/
std::shared_ptr<ProgramNode> MockASTs::Expression::mock0() {
    // BASE_TEMPLATE [START] //
    // (links) main_program -> procedure -> procStmtList
    const std::string DEFAULT_PROGRAM_NAME = "main";
    auto programNode = std::make_shared<ProgramNode>(DEFAULT_PROGRAM_NAME);
    auto proc = std::make_shared<ProcedureNode>("p");
    auto procStmtList = proc->getStmtList();
    programNode->addChild(proc);
    // --------------------- //

    // >>> proc_STMTLIST [START] <<<
    int stmtNum = 1;

    // Statement 1
    auto assign1 = std::make_shared<AssignNode>("x", stmtNum++);
    auto expr1 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<ConstantNode>("1"),
                                                        std::make_shared<ConstantNode>("2"));
    assign1->addChild(expr1);

    // Statement 2
    auto assign2 = std::make_shared<AssignNode>("y", stmtNum++);
    auto expr2 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<ConstantNode>("3"),
                                                        std::make_shared<VariableNode>("x"));
    assign2->addChild(expr2);

    // Statement 3
    auto assign3 = std::make_shared<AssignNode>("z", stmtNum++);
    auto expr3 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<VariableNode>("x"),
                                                        std::make_shared<VariableNode>("y"));
    assign3->addChild(expr3);

    procStmtList->addChild(assign1);
    procStmtList->addChild(assign2);
    procStmtList->addChild(assign3);
    // >>> proc_STMTLIST [END] <<<

    return programNode;
}
