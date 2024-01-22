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
 Procedure p1 {
   x = y;
 }
 Procedure p2 {
   call p1;
 }
 Procedure p3 {
   call p2;
 }
*/
// -------------- TREE
/*
//    main
//    ├── p1
//    │   └── StmtList
//    │        └── Assign
//    │            ├── Variable (x)
//    │            └── Variable (y)
//    ├── p2
//    │   └── StmtList
//    │       └── Call
//    │           └── Procedure (p1)
//    └── p3
//        └── StmtList
//            └── Call
//                └── Procedure (p2)
*/
std::shared_ptr<ProgramNode> MockASTs::MultiProcedureCalls::mock0() {
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
    // x = y;
    auto assignX = std::make_shared<AssignNode>("x", stmtNum++);
    auto varY = std::make_shared<VariableNode>("y");
    assignX->addChild(varY);
    proc1StmtList->addChild(assignX);
    // >>> proc1_STMTLIST [END] <<<

    // >>> proc2_STMTLIST [START] <<<
    // call p1;
    auto callP1 = std::make_shared<CallNode>("p1", stmtNum++);
    proc2StmtList->addChild(callP1);
    // >>> proc2_STMTLIST [END] <<<

    // >>> proc3_STMTLIST [START] <<<
    // call p2;
    auto callP2 = std::make_shared<CallNode>("p2", stmtNum++);
    proc3StmtList->addChild(callP2);
    // >>> proc3_STMTLIST [END] <<<

    return programNode;
}

// -------------- CODE
/*
// Procedure p1 {
//   x = y;
// }
// Procedure p2 {
//   call p1;
// }
// Procedure p3 {
//   call p2;
// }
// Procedure p4 {
//   call p3;
// }
// Procedure p5 {
//   call p4;
// }
*/
// -------------- TREE
/*
//    main
//    ├── p1
//    │   └── StmtList
//    │        └── Assign
//    │            ├── Variable (x)
//    │            └── Variable (y)
//    ├── p2
//    │   └── StmtList
//    │       └── Call
//    │           └── Procedure (p1)
//    └── p3
//        └── StmtList
//            └── Call
//                └── Procedure (p2)
*/
std::shared_ptr<ProgramNode> MockASTs::MultiProcedureCalls::mock1() {
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
    auto proc4 = std::make_shared<ProcedureNode>("p4");
    auto proc4StmtList = proc4->getStmtList();
    auto proc5 = std::make_shared<ProcedureNode>("p5");
    auto proc5StmtList = proc5->getStmtList();

    programNode->addChild(proc1);
    programNode->addChild(proc2);
    programNode->addChild(proc3);
    programNode->addChild(proc4);
    programNode->addChild(proc5);
    // BASE_TEMPLATE [END]

    // >>> proc1_STMTLIST [START] <<<
    // x = y;
    auto assignX = std::make_shared<AssignNode>("x", stmtNum++);
    auto varY = std::make_shared<VariableNode>("y");
    assignX->addChild(varY);
    proc1StmtList->addChild(assignX);
    // >>> proc1_STMTLIST [END] <<<

    // >>> proc2_STMTLIST [START] <<<
    // call p1;
    auto callP1 = std::make_shared<CallNode>("p1", stmtNum++);
    proc2StmtList->addChild(callP1);
    // >>> proc2_STMTLIST [END] <<<

    // >>> proc3_STMTLIST [START] <<<
    // call p2;
    auto callP2 = std::make_shared<CallNode>("p2", stmtNum++);
    proc3StmtList->addChild(callP2);
    // >>> proc3_STMTLIST [END] <<<

    // >>> proc4_STMTLIST [START] <<<
    // call p2;
    auto callP3 = std::make_shared<CallNode>("p3", stmtNum++);
    proc4StmtList->addChild(callP3);
    // >>> proc4_STMTLIST [END] <<<

    // >>> proc5_STMTLIST [START] <<<
    // call p2;
    auto callP4 = std::make_shared<CallNode>("p4", stmtNum++);
    proc5StmtList->addChild(callP4);
    // >>> proc5_STMTLIST [END] <<<
    return programNode;
}

// Code:
/*
Procedure A {
1	while (1 == 1) {
2		while (1==1) {
3			call B;
        }
    }
}

Procedure B {
4	print x
5   read y
}

Procedure C {
6	while (1==1) {
7		call A;
    }
}
*/

// -------------- TREE
/*
main
├── Procedure A
│   └── StmtList
│       └── While (1 == 1)
│           └── StmtList
│               └── While (1 == 1)
│                   └── StmtList
│                       └── Call B
├── Procedure B
│   └── StmtList
│       └── Print x
│       └── Read y
└── Procedure C
    └── StmtList
        └── While (1 == 1)
            └── StmtList
                └── Call A

*/
std::shared_ptr<ProgramNode> MockASTs::MultiProcedureCalls::mock2() {
    int stmtNum = 1;

    // BASE_TEMPLATE [START]
    const std::string DEFAULT_PROGRAM_NAME = "main";
    auto programNode = std::make_shared<ProgramNode>(DEFAULT_PROGRAM_NAME);
    auto procA = std::make_shared<ProcedureNode>("A");
    auto procAStmtList = procA->getStmtList();
    auto procB = std::make_shared<ProcedureNode>("B");
    auto procBStmtList = procB->getStmtList();
    auto procC = std::make_shared<ProcedureNode>("C");
    auto procCStmtList = procC->getStmtList();

    programNode->addChild(procA);
    programNode->addChild(procB);
    programNode->addChild(procC);
    // BASE_TEMPLATE [END]

    // >>> procA_STMTLIST [START] <<<
    // while (1 == 1) {...}
    auto whileStmtNum = stmtNum++;
    auto whileCondition = std::make_shared<BinaryExpressionNode>("==", std::make_shared<ConstantNode>("1"),
                                                                 std::make_shared<ConstantNode>("1"));
    auto whileStmtList = std::make_shared<StmtListNode>();

    // start nested while (1 == 1) { call B }
    auto while2StmtNum = stmtNum++;
    auto while2Condition = std::make_shared<BinaryExpressionNode>("==", std::make_shared<ConstantNode>("1"),
                                                                  std::make_shared<ConstantNode>("1"));
    auto while2StmtList = std::make_shared<StmtListNode>();
    auto callB = std::make_shared<CallNode>("B", stmtNum++);
    while2StmtList->addChild(callB);
    auto while2Node = std::make_shared<WhileThenNode>(while2Condition, while2StmtList, while2StmtNum);
    // end nested while

    whileStmtList->addChild(while2Node);
    auto whileNode = std::make_shared<WhileThenNode>(whileCondition, whileStmtList, whileStmtNum);

    procAStmtList->addChild(whileNode);
    // >>> procA_STMTLIST [END] <<<

    // >>> procB_STMTLIST [START] <<<
    auto printX = std::make_shared<PrintNode>("x", stmtNum++);
    procBStmtList->addChild(printX);

    auto readY = std::make_shared<ReadNode>("y", stmtNum++);
    procBStmtList->addChild(readY);
    // >>> procB_STMTLIST [END] <<<

    // >>> procC_STMTLIST [START] <<<
    // while (1 == 1) { call A }
    auto while3StmtNum = stmtNum++;
    auto while3Condition = std::make_shared<BinaryExpressionNode>("==", std::make_shared<ConstantNode>("1"),
                                                                  std::make_shared<ConstantNode>("1"));
    auto while3StmtList = std::make_shared<StmtListNode>();
    auto callA = std::make_shared<CallNode>("A", stmtNum++);
    while3StmtList->addChild(callA);
    auto while3Node = std::make_shared<WhileThenNode>(while3Condition, while3StmtList, while3StmtNum);

    procCStmtList->addChild(while3Node);
    // >>> procC_STMTLIST [END] <<<

    return programNode;
}

// Code:
/*
    Procedure A {
1        print x;
2        if (y < 0) {
3            print y;
4            call B;
        } else {
5            while (z == 0) {
6                print w;
7                call C;
            }
        }
    }

    Procedure B {
8       call D;
    }

    Procedure C {
9        read i;
    }

    Procedure D {
10      print m;
11      call C
    };


*/
// -------------- TREE
/*
    main
    ├── A
    │   └── StmtList
    │        ├── Print
    │        │   └── Variable (x)
    │        └── IfThenElse
    │            ├── BinaryExpr (<)
    │            │   ├── Variable (y)
    │            │   └── Constant (0)
    │            ├── StmtList
    │            │   ├── Print
    │            │   │   └── Variable (y)
    │            │   └── Call
    │            │       └── Procedure (p1)
    │            └── StmtList
    │                └── WhileThen
    │                   ├── BinaryExpression (=)
    │                   │   ├── Variable (x)
    │                   │   └── Constant (0)
    │                   └── StmtList
    │                       ├── Print
    │                       │   └── Variable (w)
    │                       └── Call
    │                           └── Procedure (c)
    │
    ├── B
    │   └── StmtList
    │       └── Call
    │           └── Procedure (D)
    ├── C
    │   └── Read
    │       └── Variable (i)
    │
    └── D
        └── StmtList
            ├── Print
            │   └── Variable (m)
            └── Call
                └── Procedure (C)
*/
std::shared_ptr<ProgramNode> MockASTs::MultiProcedureCalls::mock3() {
    int stmtNum = 1;

    // BASE_TEMPLATE [START]
    const std::string DEFAULT_PROGRAM_NAME = "main";
    auto programNode = std::make_shared<ProgramNode>(DEFAULT_PROGRAM_NAME);
    auto procA = std::make_shared<ProcedureNode>("A");
    auto procAStmtList = procA->getStmtList();
    auto procB = std::make_shared<ProcedureNode>("B");
    auto procBStmtList = procB->getStmtList();
    auto procC = std::make_shared<ProcedureNode>("C");
    auto procCStmtList = procC->getStmtList();
    auto procD = std::make_shared<ProcedureNode>("D");
    auto procDStmtList = procD->getStmtList();

    programNode->addChild(procA);
    programNode->addChild(procB);
    programNode->addChild(procC);
    programNode->addChild(procD);
    // BASE_TEMPLATE [END]

    // >>> procA_STMTLIST [START] <<<
    // print x;
    auto printX = std::make_shared<PrintNode>("x", stmtNum++);
    procAStmtList->addChild(printX);

    // if (y < 0) {...} else {...}
    auto ifStmtNum = stmtNum++;
    auto ifCondition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("y"),
                                                              std::make_shared<ConstantNode>("0"));
    auto ifThen = std::make_shared<StmtListNode>();
    auto ifElse = std::make_shared<StmtListNode>();

    // print y;
    auto printY = std::make_shared<PrintNode>("y", stmtNum++);
    ifThen->addChild(printY);

    // call B;
    auto callB = std::make_shared<CallNode>("B", stmtNum++);
    ifThen->addChild(callB);

    // while (z == 0) {...}
    auto whileStmtNum = stmtNum++;
    auto whileCondition = std::make_shared<BinaryExpressionNode>("==", std::make_shared<VariableNode>("z"),
                                                                 std::make_shared<ConstantNode>("0"));
    auto whileStmtList = std::make_shared<StmtListNode>();

    // print w;
    auto printW = std::make_shared<PrintNode>("w", stmtNum++);
    whileStmtList->addChild(printW);

    // call C;
    auto callC = std::make_shared<CallNode>("C", stmtNum++);
    whileStmtList->addChild(callC);

    auto whileNode = std::make_shared<WhileThenNode>(whileCondition, whileStmtList, whileStmtNum);

    ifElse->addChild(whileNode);

    auto ifNode = std::make_shared<IfThenElseNode>(ifCondition, ifThen, ifElse, ifStmtNum);

    procAStmtList->addChild(ifNode);
    // >>> procA_STMTLIST [END] <<<

    // >>> procB_STMTLIST [START] <<<
    // call D;
    auto callD = std::make_shared<CallNode>("D", stmtNum++);
    procBStmtList->addChild(callD);
    // >>> procB_STMTLIST [END] <<<

    // >>> procC_STMTLIST [START] <<<
    // read i;
    auto readI = std::make_shared<ReadNode>("i", stmtNum++);
    procCStmtList->addChild(readI);
    // >>> procC_STMTLIST [END] <<<

    // >>> procD_STMTLIST [START] <<<
    // print m;
    auto printM = std::make_shared<PrintNode>("m", stmtNum++);
    procDStmtList->addChild(printM);
    // call C;
    auto callCInD = std::make_shared<CallNode>("C", stmtNum++);
    procDStmtList->addChild(callCInD);
    // >>> procD_STMTLIST [END] <<<

    return programNode;
}
