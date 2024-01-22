#include "MockASTs.h"
#include "SP/AST/AssignNode.h"
#include "SP/AST/BinaryExpressionNode.h"
#include "SP/AST/CallNode.h"
#include "SP/AST/ConstantNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/PrintNode.h"
#include "SP/AST/ProcedureNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/AST/ReadNode.h"
#include "SP/AST/StmtListNode.h"
#include "SP/AST/VariableNode.h"
#include "SP/AST/WhileThenNode.h"
#include "catch.hpp"

// ai-gen start (gpt3, 3)
TEST_CASE("Should be declared with correct type and values", "[ASTNode]") {
    int MOCK_STMT_NUM = 0;
    SECTION("Program Node") {
        const std::string PROGRAM_NAME = "main";
        auto programNode = std::make_shared<ProgramNode>(PROGRAM_NAME);
        REQUIRE(programNode->getType() == NodeType::PROGRAM);
        REQUIRE(programNode->getValue() == PROGRAM_NAME);
    }
    SECTION("Procedure Node") {
        const std::string PROCEDURE_NAME = "p";
        auto procedureNode = std::make_shared<ProcedureNode>(PROCEDURE_NAME);
        REQUIRE(procedureNode->getType() == NodeType::PROCEDURE);
        REQUIRE(procedureNode->getValue() == PROCEDURE_NAME);
    }
    SECTION("StmtList Node") {
        auto stmtListNode = std::make_shared<StmtListNode>();
        REQUIRE(stmtListNode->getType() == NodeType::STMT_LIST);
    }
    SECTION("WhileThen Node") {
        auto whileThenNode = std::make_shared<WhileThenNode>(MOCK_STMT_NUM);
        REQUIRE(whileThenNode->getType() == NodeType::WHILE_THEN);
    }
    SECTION("IfThenElse Node") {
        auto ifThenElseNode = std::make_shared<IfThenElseNode>(MOCK_STMT_NUM);
        REQUIRE(ifThenElseNode->getType() == NodeType::IF_THEN_ELSE);
        REQUIRE(ifThenElseNode->getStmtNum() == MOCK_STMT_NUM);
    }
    SECTION("Variable Node") {
        const std::string VARIABLE_NAME = "x";
        auto variableNode = std::make_shared<VariableNode>(VARIABLE_NAME);
        REQUIRE(variableNode->getType() == NodeType::VARIABLE);
        REQUIRE(variableNode->getValue() == VARIABLE_NAME);
    }
    SECTION("Constant Node") {
        const std::string CONSTANT_VALUE = "31";
        auto constantNode = std::make_shared<ConstantNode>(CONSTANT_VALUE);
        REQUIRE(constantNode->getType() == NodeType::CONSTANT);
        REQUIRE(constantNode->getValue() == CONSTANT_VALUE);
        REQUIRE(constantNode->getIntValue() == 31);
    }
    SECTION("Read Node") {
        auto readNode = std::make_shared<ReadNode>("x", MOCK_STMT_NUM);
        REQUIRE(readNode->getType() == NodeType::READ);
        //        REQUIRE(readNode->getVarNode() == std::make_shared<VariableNode>("x"));
        REQUIRE(readNode->getStmtNum() == MOCK_STMT_NUM);
    }
    SECTION("Print Node") {
        auto printNode = std::make_shared<PrintNode>("x", MOCK_STMT_NUM);
        REQUIRE(printNode->getType() == NodeType::PRINT);
        //        REQUIRE(printNode->getVarNode() == std::make_shared<VariableNode>("x"));
        REQUIRE(printNode->getStmtNum() == MOCK_STMT_NUM);
    }
    SECTION("Assign Node") {
        auto assignNode = std::make_shared<AssignNode>("x", MOCK_STMT_NUM);
        REQUIRE(assignNode->getType() == NodeType::ASSIGN);
        //        REQUIRE(assignNode->getVarNode() == std::make_shared<VariableNode>("x"));
        REQUIRE(assignNode->getStmtNum() == MOCK_STMT_NUM);
        //        REQUIRE_THROWS_AS(assignNode->getAssignedNode(), std::runtime_error);
    }
    SECTION("Call Node") {
        const std::string procName = "p2";
        auto callNode = std::make_shared<CallNode>(procName, MOCK_STMT_NUM);
        REQUIRE(callNode->getType() == NodeType::CALL);
        REQUIRE(callNode->getStmtNum() == MOCK_STMT_NUM);
        REQUIRE(callNode->getValue() == procName);
    }
}

TEST_CASE("Should be able to build a tree", "[ASTNode]") {
    SECTION("mock0 - minimal program;  [USES: breadthFirstTraversal(), toString()]") {
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
        auto programNode = MockASTs::mock0();
        auto traversalResult = programNode->breadthFirstTraversal();
        REQUIRE(traversalResult.size() == 3);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
    }

    SECTION("mock1 - small program (read, assign, print); [USES: breadthFirstTraversal(), toString()]") {
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
        auto programNode = MockASTs::mock1();
        auto traversalResult = programNode->breadthFirstTraversal();
        REQUIRE(traversalResult.size() == 10);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::ASSIGN);
        REQUIRE(traversalResult[4]->getType() == NodeType::READ);
        REQUIRE(traversalResult[5]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[6]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[7]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[8]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[8]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: Assign]");
        REQUIRE(traversalResult[4]->toString() == "2: [: Read]");
        REQUIRE(traversalResult[5]->toString() == "3: [: Print]");
        REQUIRE(traversalResult[6]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[7]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[8]->toString() == "[y: Variable]");
        REQUIRE(traversalResult[9]->toString() == "[x: Variable]");
    }

    SECTION("mock2 - small program (read, if, while); [USES: breadthFirstTraversal(), toString()]") {
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
        auto programNode = MockASTs::mock2();
        auto traversalResult = programNode->breadthFirstTraversal();
        REQUIRE(traversalResult.size() == 24);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);

        REQUIRE(traversalResult[3]->getType() == NodeType::READ);
        REQUIRE(traversalResult[4]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[5]->getType() == NodeType::READ);
        REQUIRE(traversalResult[6]->getType() == NodeType::IF_THEN_ELSE);

        REQUIRE(traversalResult[7]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[8]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[9]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[10]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[11]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[12]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[13]->getType() == NodeType::STMT_LIST);

        REQUIRE(traversalResult[14]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[15]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[16]->getType() == NodeType::READ);
        REQUIRE(traversalResult[17]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[18]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[19]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[20]->getType() == NodeType::PRINT);

        REQUIRE(traversalResult[21]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[22]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[23]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");

        REQUIRE(traversalResult[3]->toString() == "1: [: Read]");
        REQUIRE(traversalResult[4]->toString() == "2: [: WhileThen]");
        REQUIRE(traversalResult[5]->toString() == "4: [: Read]");
        REQUIRE(traversalResult[6]->toString() == "5: [: IfThenElse]");

        REQUIRE(traversalResult[7]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[8]->toString() == "[<: BinaryExpression]");
        REQUIRE(traversalResult[9]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[10]->toString() == "[y: Variable]");
        REQUIRE(traversalResult[11]->toString() == "[<: BinaryExpression]");
        REQUIRE(traversalResult[12]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[13]->toString() == "[: StmtList]");

        REQUIRE(traversalResult[14]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[15]->toString() == "[0: Constant]");
        REQUIRE(traversalResult[16]->toString() == "3: [: Read]");
        REQUIRE(traversalResult[17]->toString() == "[y: Variable]");
        REQUIRE(traversalResult[18]->toString() == "[0: Constant]");
        REQUIRE(traversalResult[19]->toString() == "6: [: Print]");
        REQUIRE(traversalResult[20]->toString() == "7: [: Print]");

        REQUIRE(traversalResult[21]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[22]->toString() == "[y: Variable]");
        REQUIRE(traversalResult[23]->toString() == "[x: Variable]");
    }
}
// ai-gen end
