#include "SP/Parser/Parser.h"
#include "SP/Parser/ParserException.h"
#include "catch.hpp"

// Test the Tokenizer class
TEST_CASE("Parse assign statements", "[assignParser]") {
    SECTION("Parsing of simple assign stmt") {
        std::string input = "Procedure p {x = 2;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();
        REQUIRE(traversalResult.size() == 6);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::ASSIGN);
        REQUIRE(traversalResult[4]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[5]->getType() == NodeType::CONSTANT);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: Assign]");
        REQUIRE(traversalResult[4]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[5]->toString() == "[2: Constant]");
    }

    SECTION("Parsing of assign stmt with add followed by multiply") {
        std::string input = "Procedure p {x = a + b * 2 ;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 10);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::ASSIGN);
        REQUIRE(traversalResult[4]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[5]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[6]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[7]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[8]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[9]->getType() == NodeType::CONSTANT);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: Assign]");
        REQUIRE(traversalResult[4]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[5]->toString() == "[+: BinaryExpression]");
        REQUIRE(traversalResult[6]->toString() == "[a: Variable]");
        REQUIRE(traversalResult[7]->toString() == "[*: BinaryExpression]");
        REQUIRE(traversalResult[8]->toString() == "[b: Variable]");
        REQUIRE(traversalResult[9]->toString() == "[2: Constant]");
    }

    SECTION("Parsing of assign stmt with add followed by multiply") {
        std::string input = "Procedure p {x = (a + b) * 2 ;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 10);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::ASSIGN);
        REQUIRE(traversalResult[4]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[5]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[6]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[7]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[8]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[9]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: Assign]");
        REQUIRE(traversalResult[4]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[5]->toString() == "[*: BinaryExpression]");
        REQUIRE(traversalResult[6]->toString() == "[+: BinaryExpression]");
        REQUIRE(traversalResult[7]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[8]->toString() == "[a: Variable]");
        REQUIRE(traversalResult[9]->toString() == "[b: Variable]");
    }

    SECTION("Missing semicolon should throw error") {
        std::string input = "Procedure p {x = (a + b) * 2 }";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("Missing Var/Const should throw error") {
        std::string input = "Procedure p {x = (a + b) *  ;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("Invalid ordering of const/vars") {
        std::string input = "Procedure p {x = (x z + 5 );}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    // Add more test cases as needed...
}
