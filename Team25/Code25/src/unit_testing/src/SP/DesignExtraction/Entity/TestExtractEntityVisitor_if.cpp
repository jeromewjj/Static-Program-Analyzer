#include "../../AST/MockNodes.h"
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
#include "SP/DesignExtraction/Entity/ExtractEntityVisitor.h"
#include "catch.hpp"

namespace Helper_ExtractIf {
    const int MOCK_STMT_NUM = 404;

    // if (y < 0) then { print y; } else { print x; }
    namespace If1 {
        auto if1_stmtNum = 1;
        auto if1_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("y"),
                                                                    std::make_shared<ConstantNode>("0"));
        auto if1_then = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("y", MOCK_STMT_NUM)}));
        auto if1_else = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("x", MOCK_STMT_NUM)}));
        const auto condVars = unordered_set<string>{"y"};
        const auto node = std::make_shared<IfThenElseNode>(if1_condition, if1_then, if1_else, if1_stmtNum);
    }

    // if (y == z) then { print y; } else { print x; }
    namespace If2 {
        auto if2_stmtNum = 1;
        auto if2_condition = std::make_shared<BinaryExpressionNode>("==", std::make_shared<VariableNode>("y"),
                                                                    std::make_shared<VariableNode>("z"));
        auto if2_then = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("y", MOCK_STMT_NUM)}));
        auto if2_else = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("x", MOCK_STMT_NUM)}));
        const auto condVars = unordered_set<string>{"y", "z"};
        const auto node = std::make_shared<IfThenElseNode>(if2_condition, if2_then, if2_else, if2_stmtNum);
    }

    // if (1 < 0) then { print y; } else { print x; }
    namespace If3 {
        auto if3_stmtNum = 1;
        auto if3_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<ConstantNode>("1"),
                                                                    std::make_shared<ConstantNode>("0"));
        auto if3_then = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("y", MOCK_STMT_NUM)}));
        auto if3_else = std::make_shared<StmtListNode>(StmtListNode({std::make_shared<PrintNode>("x", MOCK_STMT_NUM)}));
        const auto node = std::make_shared<IfThenElseNode>(if3_condition, if3_then, if3_else, if3_stmtNum);
    }

    // while (x < 0) { read x; }
    namespace While1 {
        auto while1_stmtNum = 1;
        auto while1_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("x"),
                                                                       std::make_shared<ConstantNode>("0"));
        auto while1_stmtList =
            std::make_shared<StmtListNode>(StmtListNode({std::make_shared<ReadNode>("x", MOCK_STMT_NUM)}));
        const auto node = std::make_shared<WhileThenNode>(while1_condition, while1_stmtList, while1_stmtNum);
    }
}

TEST_CASE("INDIVIDUAL_NODE: should extract IfNode correctly", "[ExtractEntitytVisitor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();

    SECTION("should extract (ifNode with 1 condVar)") {
        ExtractEntityVisitor e_v{pkbAdapter};
        auto ifNode = Helper_ExtractIf::If1::node;
        auto stmtNum = Helper_ExtractIf::If1::if1_stmtNum;
        auto condVars = Helper_ExtractIf::If1::condVars;
        ifNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_IF_COND_VARS{{stmtNum, condVars}};

        // assert
        REQUIRE(e_v.getIfCondVars() == EXPECTED_IF_COND_VARS);
    }

    SECTION("should extract (ifNode with 2 condVar)") {
        ExtractEntityVisitor e_v{pkbAdapter};
        auto ifNode = Helper_ExtractIf::If2::node;
        auto stmtNum = Helper_ExtractIf::If2::if2_stmtNum;
        auto condVars = Helper_ExtractIf::If2::condVars;
        ifNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_IF_COND_VARS{{stmtNum, condVars}};

        // assert
        REQUIRE(e_v.getIfCondVars() == EXPECTED_IF_COND_VARS);
    }

    SECTION("should extract nothing (ifNode with no cond vars)") {
        ExtractEntityVisitor e_v{pkbAdapter};
        auto ifNode = Helper_ExtractIf::If3::node;
        ifNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_IF_COND_VARS{};

        // assert
        REQUIRE(e_v.getIfCondVars() == EXPECTED_IF_COND_VARS);
    }

    // test that method overloading works
    SECTION("should extract despite generic type; dynamic dispatch / runtime polymorphism") {
        ExtractEntityVisitor e_v{pkbAdapter};
        ASTNodePtr upcasted_ifNode = Helper_ExtractIf::If1::node;
        auto stmtNum = Helper_ExtractIf::If1::if1_stmtNum;
        auto condVars = Helper_ExtractIf::If1::condVars;
        upcasted_ifNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_IF_COND_VARS{{stmtNum, condVars}};

        // assert
        REQUIRE(e_v.getIfCondVars() == EXPECTED_IF_COND_VARS);
    }

    SECTION("should not extract") {
        int MOCK_STMT_NUM = 0;

        auto constant3 = std::make_shared<ConstantNode>("3");
        auto varX = std::make_shared<VariableNode>("x");

        auto programNode = std::make_shared<ProgramNode>("main");
        auto procedureNode = std::make_shared<ProcedureNode>("p");
        auto stmtListNode = std::make_shared<StmtListNode>();

        auto whileThenNode = Helper_ExtractIf::While1::node;
        auto readNode = std::make_shared<ReadNode>("x", MOCK_STMT_NUM);
        auto printNode = std::make_shared<PrintNode>("x", MOCK_STMT_NUM);
        auto assignNode = MockAssignments::mock0(); // x = 1 + 2
        auto callNode = std::make_shared<CallNode>("p2", MOCK_STMT_NUM);

        ExtractEntityVisitor e_v{pkbAdapter};
        varX->acceptVisitor(e_v);
        constant3->acceptVisitor(e_v);
        programNode->acceptVisitor(e_v);
        procedureNode->acceptVisitor(e_v);
        stmtListNode->acceptVisitor(e_v);
        whileThenNode->acceptVisitor(e_v);
        readNode->acceptVisitor(e_v);
        printNode->acceptVisitor(e_v);
        assignNode->acceptVisitor(e_v);
        callNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_IF_COND_VARS{};

        // assert
        REQUIRE(e_v.getIfCondVars() == EXPECTED_IF_COND_VARS);
    }
}
