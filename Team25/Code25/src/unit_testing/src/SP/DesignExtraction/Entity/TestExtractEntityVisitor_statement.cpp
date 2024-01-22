#include "../../AST/MockNodes.h"
#include "SP/AST/AssignNode.h"
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
#include "SP/DesignExtraction/Entity/ExtractCategoryVisitor.h"
#include "catch.hpp"

TEST_CASE("Should extract statement correctly", "[ExtractEntityVisitor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();

    auto constant3 = std::make_shared<ConstantNode>("3");
    auto varX = std::make_shared<VariableNode>("x");

    auto programNode = std::make_shared<ProgramNode>("main");
    auto procedureNode = std::make_shared<ProcedureNode>("p");
    auto stmtListNode = std::make_shared<StmtListNode>();

    auto whileThenNode = MockWhile::mock0();
    auto ifThenElseNode = MockIf::mock0();
    auto readNode = std::make_shared<ReadNode>("x", MOCK_STMT_NUM);
    auto printNode = std::make_shared<PrintNode>("x", MOCK_STMT_NUM);
    auto assignNode = MockAssignments::mock0(); // 1. "x = 1 + 2"
    auto callNode = std::make_shared<CallNode>("p2", MOCK_STMT_NUM);

    SECTION("should extract") {
        ExtractCategoryVisitor s_e{pkbAdapter};
        whileThenNode->acceptVisitor(s_e);
        ifThenElseNode->acceptVisitor(s_e);
        readNode->acceptVisitor(s_e);
        printNode->acceptVisitor(s_e);
        assignNode->acceptVisitor(s_e);
        callNode->acceptVisitor(s_e);

        // expected
        std::vector<std::pair<NodeType, int>> EXPECTED_STMTS{
            {NodeType::WHILE_THEN, 1},        {NodeType::IF_THEN_ELSE, 1}, {NodeType::READ, MOCK_STMT_NUM},
            {NodeType::PRINT, MOCK_STMT_NUM}, {NodeType::ASSIGN, 1},       {NodeType::CALL, MOCK_STMT_NUM},
        };

        // assert
        REQUIRE(s_e.getStmts() == EXPECTED_STMTS);
    }

    // test that method overloading works
    SECTION("should extract despite generic type; dynamic dispatch / runtime polymorphism") {
        ExtractCategoryVisitor s_e{pkbAdapter};
        ASTNodePtr upcasted_whileThenNode = std::make_shared<WhileThenNode>(1);
        ASTNodePtr upcasted_ifThenElseNode = std::make_shared<IfThenElseNode>(2);
        ASTNodePtr upcasted_readNode = std::make_shared<ReadNode>("x", 3);
        ASTNodePtr upcasted_printNode = std::make_shared<PrintNode>("x", 4);
        ASTNodePtr upcasted_assignNode = MockAssignments::mock0(); // 1. "x = 1 + 2"
        ASTNodePtr upcasted_callNode = std::make_shared<CallNode>("p2", 6);

        upcasted_whileThenNode->acceptVisitor(s_e);
        upcasted_ifThenElseNode->acceptVisitor(s_e);
        upcasted_readNode->acceptVisitor(s_e);
        upcasted_printNode->acceptVisitor(s_e);
        upcasted_assignNode->acceptVisitor(s_e);
        upcasted_callNode->acceptVisitor(s_e);

        // expected
        std::vector<std::pair<NodeType, int>> EXPECTED_STMTS{
            {NodeType::WHILE_THEN, 1}, {NodeType::IF_THEN_ELSE, 2}, {NodeType::READ, 3},
            {NodeType::PRINT, 4},      {NodeType::ASSIGN, 1},       {NodeType::CALL, 6},
        };

        // assert
        REQUIRE(s_e.getStmts() == EXPECTED_STMTS);
    }

    SECTION("Should not extract statement from nodes which are not statement node types") {
        ExtractCategoryVisitor s_e{pkbAdapter};
        constant3->acceptVisitor(s_e);
        varX->acceptVisitor(s_e);
        programNode->acceptVisitor(s_e);
        procedureNode->acceptVisitor(s_e);
        stmtListNode->acceptVisitor(s_e);

        // expected
        std::vector<std::pair<NodeType, int>> EXPECTED_STMTS{};

        // assert
        REQUIRE(s_e.getStmts() == EXPECTED_STMTS);
    }
}
