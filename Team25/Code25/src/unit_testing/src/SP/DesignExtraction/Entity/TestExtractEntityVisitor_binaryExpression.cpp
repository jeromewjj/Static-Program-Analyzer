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

TEST_CASE("INDIVIDUAL_NODE: extract binary expression", "[ExtractEntitytVisitor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    int MOCK_STMT_NUM = 0;

    int stmtNum = 1;

    auto binaryExpr1 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<ConstantNode>("1"),
                                                              std::make_shared<ConstantNode>("2"));
    auto binaryExpr2 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<ConstantNode>("3"),
                                                              std::make_shared<VariableNode>("x"));
    auto binaryExpr3 = std::make_shared<BinaryExpressionNode>("+", std::make_shared<VariableNode>("x"),
                                                              std::make_shared<VariableNode>("y"));

    auto constant3 = std::make_shared<ConstantNode>("3");
    auto varX = std::make_shared<VariableNode>("x");

    auto programNode = std::make_shared<ProgramNode>("main");
    auto procedureNode = std::make_shared<ProcedureNode>("p");
    auto stmtListNode = std::make_shared<StmtListNode>();

    auto whileThenNode = MockWhile::mock0();
    auto ifThenElseNode = MockIf::mock0();
    auto readNode = std::make_shared<ReadNode>("x", MOCK_STMT_NUM);
    auto printNode = std::make_shared<PrintNode>("x", MOCK_STMT_NUM);
    auto assignNode = MockAssignments::mock0(); // x = 1 + 2
    auto callNode = std::make_shared<CallNode>("p2", MOCK_STMT_NUM);

    SECTION("should extract") {
        ExtractEntityVisitor e_v{pkbAdapter};
        binaryExpr1->acceptVisitor(e_v);
        binaryExpr2->acceptVisitor(e_v);
        binaryExpr3->acceptVisitor(e_v);

        // expected
        std::unordered_set<std::string> EXPECTED_VARS{};

        // assert
        REQUIRE(e_v.getVars() == EXPECTED_VARS);
    }

    // test that method overloading works
    SECTION("should extract despite generic type; dynamic dispatch / runtime polymorphism") {
        ExtractEntityVisitor e_v{pkbAdapter};

        ASTNodePtr upcasted_varY = std::make_shared<VariableNode>("y");
        upcasted_varY->acceptVisitor(e_v);

        // expected
        std::unordered_set<std::string> EXPECTED_VARS{"y"};

        // assert
        REQUIRE(e_v.getVars() == EXPECTED_VARS);
    }

    SECTION("should not extract variables") {
        ExtractEntityVisitor e_v{pkbAdapter};
        constant3->acceptVisitor(e_v);
        programNode->acceptVisitor(e_v);
        procedureNode->acceptVisitor(e_v);
        stmtListNode->acceptVisitor(e_v);
        whileThenNode->acceptVisitor(e_v);
        ifThenElseNode->acceptVisitor(e_v);
        readNode->acceptVisitor(e_v);
        printNode->acceptVisitor(e_v);
        assignNode->acceptVisitor(e_v);
        callNode->acceptVisitor(e_v);

        // expected
        std::unordered_set<std::string> EXPECTED_VARS{};

        // assert
        REQUIRE(e_v.getVars() == EXPECTED_VARS);
    }
}
