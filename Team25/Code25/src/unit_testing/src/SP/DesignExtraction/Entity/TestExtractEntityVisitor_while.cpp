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

namespace Helper_ExtractWhile {
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

    // while (x < 0) { read x; }
    namespace While1 {
        auto while1_stmtNum = 1;
        auto while1_condition = std::make_shared<BinaryExpressionNode>("<", std::make_shared<VariableNode>("x"),
                                                                       std::make_shared<ConstantNode>("0"));
        auto while1_stmtList =
            std::make_shared<StmtListNode>(StmtListNode({std::make_shared<ReadNode>("x", MOCK_STMT_NUM)}));
        const auto condVars = unordered_set<string>{"x"};
        const auto node = std::make_shared<WhileThenNode>(while1_condition, while1_stmtList, while1_stmtNum);
    }

    // while (x > z) { read y; }
    namespace While2 {
        auto while2_stmtNum = 1;
        auto while2_condition = std::make_shared<BinaryExpressionNode>(">", std::make_shared<VariableNode>("x"),
                                                                       std::make_shared<VariableNode>("z"));
        auto while2_stmtList =
            std::make_shared<StmtListNode>(StmtListNode({std::make_shared<ReadNode>("x", MOCK_STMT_NUM)}));
        const auto condVars = unordered_set<string>{"x", "z"};
        const auto node = std::make_shared<WhileThenNode>(while2_condition, while2_stmtList, while2_stmtNum);
    }

    // while (2 == 3) { read y; }
    namespace While3 {
        auto while3_stmtNum = 1;
        auto while3_condition = std::make_shared<BinaryExpressionNode>("==", std::make_shared<ConstantNode>("2"),
                                                                       std::make_shared<ConstantNode>("3"));
        auto while3_stmtList =
            std::make_shared<StmtListNode>(StmtListNode({std::make_shared<ReadNode>("x", MOCK_STMT_NUM)}));
        const auto condVars = unordered_set<string>{"x", "z"};
        const auto node = std::make_shared<WhileThenNode>(while3_condition, while3_stmtList, while3_stmtNum);
    }
}

TEST_CASE("INDIVIDUAL_NODE: should extract WhileNode correctly", "[ExtractEntitytVisitor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();

    SECTION("should extract (whileNode with 1 cond var)") {
        ExtractEntityVisitor e_v{pkbAdapter};
        auto whileNode = Helper_ExtractWhile::While1::node;
        auto stmtNum = Helper_ExtractWhile::While1::while1_stmtNum;
        auto condVars = Helper_ExtractWhile::While1::condVars;
        whileNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_WHILE_COND_VARS{{stmtNum, condVars}};

        // assert
        REQUIRE(e_v.getWhileCondVars() == EXPECTED_WHILE_COND_VARS);
    }

    SECTION("should extract (whileNode with 2 cond var)") {
        ExtractEntityVisitor e_v{pkbAdapter};
        auto whileNode = Helper_ExtractWhile::While2::node;
        auto stmtNum = Helper_ExtractWhile::While2::while2_stmtNum;
        auto condVars = Helper_ExtractWhile::While2::condVars;
        whileNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_WHILE_COND_VARS{{stmtNum, condVars}};

        // assert
        REQUIRE(e_v.getWhileCondVars() == EXPECTED_WHILE_COND_VARS);
    }

    SECTION("should extract nothing (whileNode with no cond vars)") {
        ExtractEntityVisitor e_v{pkbAdapter};
        auto ifNode = Helper_ExtractWhile::While3::node;
        ifNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_WHILE_COND_VARS{};

        // assert
        REQUIRE(e_v.getWhileCondVars() == EXPECTED_WHILE_COND_VARS);
    }

    // test that method overloading works
    SECTION("should extract despite generic type; dynamic dispatch / runtime polymorphism") {
        ExtractEntityVisitor e_v{pkbAdapter};
        ASTNodePtr upcasted_whileNode = Helper_ExtractWhile::While1::node;
        auto stmtNum = Helper_ExtractWhile::While1::while1_stmtNum;
        auto condVars = Helper_ExtractWhile::While1::condVars;
        upcasted_whileNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_WHILE_COND_VARS{{stmtNum, condVars}};

        // assert
        REQUIRE(e_v.getWhileCondVars() == EXPECTED_WHILE_COND_VARS);
    }

    SECTION("should not extract") {
        int MOCK_STMT_NUM = 0;

        auto constant3 = std::make_shared<ConstantNode>("3");
        auto varX = std::make_shared<VariableNode>("x");

        auto programNode = std::make_shared<ProgramNode>("main");
        auto procedureNode = std::make_shared<ProcedureNode>("p");
        auto stmtListNode = std::make_shared<StmtListNode>();

        auto ifNode = Helper_ExtractWhile::If1::node;
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
        ifNode->acceptVisitor(e_v);
        readNode->acceptVisitor(e_v);
        printNode->acceptVisitor(e_v);
        assignNode->acceptVisitor(e_v);
        callNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<int, std::unordered_set<std::string>> EXPECTED_WHILE_COND_VARS{};

        // assert
        REQUIRE(e_v.getWhileCondVars() == EXPECTED_WHILE_COND_VARS);
    }
}
