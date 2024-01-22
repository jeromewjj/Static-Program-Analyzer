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

TEST_CASE("Should extract assignment expression correctly", "[ExtractEntityVisitor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();

    auto assign1 = std::make_shared<AssignNode>("x", 1);
    auto expr1 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<ConstantNode>("1"),
                                                        std::make_shared<ConstantNode>("2"));
    assign1->addChild(expr1);

    auto assign2 = std::make_shared<AssignNode>("y", 2);
    auto expr2 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<ConstantNode>("3"),
                                                        std::make_shared<VariableNode>("x"));
    assign2->addChild(expr2);

    auto assign3 = std::make_shared<AssignNode>("z", 3);
    auto expr3 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<VariableNode>("x"),
                                                        std::make_shared<VariableNode>("y"));
    assign3->addChild(expr3);

    auto constant3 = std::make_shared<ConstantNode>("3");
    auto varX = std::make_shared<VariableNode>("x");

    auto programNode = std::make_shared<ProgramNode>("main");
    auto procedureNode = std::make_shared<ProcedureNode>("p");
    auto stmtListNode = std::make_shared<StmtListNode>();

    auto whileThenNode = MockWhile::mock0();
    auto ifThenElseNode = MockIf::mock0();
    auto readNode = std::make_shared<ReadNode>("x", MOCK_STMT_NUM);
    auto printNode = std::make_shared<PrintNode>("x", MOCK_STMT_NUM);
    auto callNode = std::make_shared<CallNode>("p2", MOCK_STMT_NUM);

    SECTION("should extract") {
        ExtractEntityVisitor e_v{pkbAdapter};
        assign1->acceptVisitor(e_v);
        assign2->acceptVisitor(e_v);
        assign3->acceptVisitor(e_v);

        // expected
        std::vector<PKB_ASSIGN> EXPECTED_STMTS{
            {1, "x", "((1)+(2))", {"(1)", "(2)", "((1)+(2))"}},
            {2, "y", "((3)+(x))", {"(3)", "(x)", "((3)+(x))"}},
            {3, "z", "((x)+(y))", {"(x)", "(y)", "((x)+(y))"}},
        };

        // assert
        REQUIRE(e_v.getAssignInfo() == EXPECTED_STMTS);
    }

    SECTION("should extract") {
        ExtractEntityVisitor e_v{pkbAdapter};
        ASTNodePtr upcasted_assign1 = assign1;
        ASTNodePtr upcasted_assign2 = assign2;
        ASTNodePtr upcasted_assign3 = assign3;

        upcasted_assign1->acceptVisitor(e_v);
        upcasted_assign2->acceptVisitor(e_v);
        upcasted_assign3->acceptVisitor(e_v);

        // expected
        std::vector<PKB_ASSIGN> EXPECTED_STMTS{
            {1, "x", "((1)+(2))", {"(1)", "(2)", "((1)+(2))"}},
            {2, "y", "((3)+(x))", {"(3)", "(x)", "((3)+(x))"}},
            {3, "z", "((x)+(y))", {"(x)", "(y)", "((x)+(y))"}},
        };

        // assert
        REQUIRE(e_v.getAssignInfo() == EXPECTED_STMTS);
    }

    SECTION("Should not extract statement from nodes which are not statement node types") {
        ExtractEntityVisitor e_v{pkbAdapter};
        constant3->acceptVisitor(e_v);
        varX->acceptVisitor(e_v);
        programNode->acceptVisitor(e_v);
        procedureNode->acceptVisitor(e_v);
        stmtListNode->acceptVisitor(e_v);

        whileThenNode->acceptVisitor(e_v);
        ifThenElseNode->acceptVisitor(e_v);
        readNode->acceptVisitor(e_v);
        printNode->acceptVisitor(e_v);
        callNode->acceptVisitor(e_v);

        // expected
        std::vector<PKB_ASSIGN> EXPECTED_STMTS{};

        // assert
        REQUIRE(e_v.getAssignInfo() == EXPECTED_STMTS);
    }
}
