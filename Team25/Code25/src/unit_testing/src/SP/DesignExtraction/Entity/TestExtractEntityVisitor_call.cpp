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
#include "SP/DesignExtraction/Entity/ExtractEntityVisitor.h"
#include "catch.hpp"

TEST_CASE("INDIVIDUAL_NODE: should extract CallNode correctly", "[ExtractEntitytVisitor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();

    SECTION("should extract") {
        ExtractEntityVisitor e_v{pkbAdapter};
        auto callNode1 = std::make_shared<CallNode>("proc_x", 1);
        auto callNode2 = std::make_shared<CallNode>("proc_x", 2);
        auto callNode3 = std::make_shared<CallNode>("proc_y", 5);
        callNode1->acceptVisitor(e_v);
        callNode2->acceptVisitor(e_v);
        callNode3->acceptVisitor(e_v);

        // expected
        std::unordered_map<string, std::unordered_set<int>> EXPECTED_PROC_AND_CALLING_STMTS{{"proc_x", {1, 2}},
                                                                                            {"proc_y", {5}}};

        // assert
        REQUIRE(e_v.getProcAndCallingStmts() == EXPECTED_PROC_AND_CALLING_STMTS);
    }

    // test that method overloading works
    SECTION("should extract despite generic type; dynamic dispatch / runtime polymorphism") {
        ExtractEntityVisitor e_v{pkbAdapter};
        ASTNodePtr upcasted_callNode = std::make_shared<CallNode>("proc_x", 1);
        upcasted_callNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<string, std::unordered_set<int>> EXPECTED_PROC_AND_CALLING_STMTS{
            {"proc_x", {1}},
        };

        // assert
        REQUIRE(e_v.getProcAndCallingStmts() == EXPECTED_PROC_AND_CALLING_STMTS);
    }

    SECTION("should not extract") {
        auto constant3 = std::make_shared<ConstantNode>("3");
        auto varX = std::make_shared<VariableNode>("x");

        auto programNode = std::make_shared<ProgramNode>("main");
        auto procedureNode = std::make_shared<ProcedureNode>("p");
        auto stmtListNode = std::make_shared<StmtListNode>();

        auto ifNode = MockIf::mock0();
        auto whileThenNode = MockWhile::mock0();
        auto readNode = std::make_shared<ReadNode>("x", MOCK_STMT_NUM);
        auto printNode = std::make_shared<PrintNode>("x", MOCK_STMT_NUM);
        auto assignNode = MockAssignments::mock0();
        auto callNode = std::make_shared<CallNode>("p2", MOCK_STMT_NUM);

        ExtractEntityVisitor e_v{pkbAdapter};
        varX->acceptVisitor(e_v);
        constant3->acceptVisitor(e_v);
        programNode->acceptVisitor(e_v);
        procedureNode->acceptVisitor(e_v);
        stmtListNode->acceptVisitor(e_v);
        ifNode->acceptVisitor(e_v);
        whileThenNode->acceptVisitor(e_v);
        readNode->acceptVisitor(e_v);
        printNode->acceptVisitor(e_v);
        assignNode->acceptVisitor(e_v);

        // expected
        std::unordered_map<string, std::unordered_set<int>> EXPECTED_PROC_AND_CALLING_STMTS{};

        // assert
        REQUIRE(e_v.getProcAndCallingStmts() == EXPECTED_PROC_AND_CALLING_STMTS);
    }
}
