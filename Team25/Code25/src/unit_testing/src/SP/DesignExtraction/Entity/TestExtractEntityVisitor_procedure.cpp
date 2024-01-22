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

TEST_CASE("Should extract procedure correctly", "[ExtractEntitytVisitor]") {
    std::shared_ptr<PKBAdapter> pkbAdapter = PKBAdapter::getEmptyPKBAdapter();
    int MOCK_STMT_NUM = 0;

    auto constant3 = std::make_shared<ConstantNode>("3");
    auto varX = std::make_shared<VariableNode>("x");

    auto programNode = std::make_shared<ProgramNode>("main");
    auto procedureNode_p1 = std::make_shared<ProcedureNode>("p1");
    auto procedureNode_p2 = std::make_shared<ProcedureNode>("p2");
    auto stmtListNode = std::make_shared<StmtListNode>();

    auto whileThenNode = MockWhile::mock0();
    auto ifThenElseNode = MockIf::mock0();
    auto readNode = std::make_shared<ReadNode>("x", MOCK_STMT_NUM);
    auto printNode = std::make_shared<PrintNode>("x", MOCK_STMT_NUM);
    auto assignNode = MockAssignments::mock0(); // 1. x = 1 + 2
    auto callNode = std::make_shared<CallNode>("p2", MOCK_STMT_NUM);

    SECTION("should extract") {
        ExtractEntityVisitor e_v{pkbAdapter};
        procedureNode_p1->acceptVisitor(e_v);
        procedureNode_p2->acceptVisitor(e_v);

        // expected
        std::unordered_set<std::string> EXPECTED_PROCEDURES{"p1", "p2"};

        // assert
        REQUIRE(e_v.getProcedures() == EXPECTED_PROCEDURES);
    }

    // test that method overloading works
    SECTION("should extract despite generic type; dynamic dispatch / runtime polymorphism") {

        ExtractEntityVisitor e_v{pkbAdapter};
        ASTNodePtr upcasted_procedureNode_p1 = std::make_shared<ProcedureNode>("p1");
        ASTNodePtr upcasted_procedureNode_p2 = std::make_shared<ProcedureNode>("p2");

        upcasted_procedureNode_p1->acceptVisitor(e_v);
        upcasted_procedureNode_p2->acceptVisitor(e_v);

        // expected
        std::unordered_set<std::string> EXPECTED_PROCEDURES{"p1", "p2"};

        // assert
        REQUIRE(e_v.getProcedures() == EXPECTED_PROCEDURES);
    }

    SECTION("should not extract") {
        ExtractEntityVisitor e_v{pkbAdapter};
        constant3->acceptVisitor(e_v);
        varX->acceptVisitor(e_v);
        programNode->acceptVisitor(e_v);
        stmtListNode->acceptVisitor(e_v);
        whileThenNode->acceptVisitor(e_v);
        ifThenElseNode->acceptVisitor(e_v);
        readNode->acceptVisitor(e_v);
        printNode->acceptVisitor(e_v);
        assignNode->acceptVisitor(e_v);
        callNode->acceptVisitor(e_v);

        // expected
        std::unordered_set<std::string> EXPECTED_PROCEDURES{};

        // assert
        REQUIRE(e_v.getProcedures() == EXPECTED_PROCEDURES);
    }
}
