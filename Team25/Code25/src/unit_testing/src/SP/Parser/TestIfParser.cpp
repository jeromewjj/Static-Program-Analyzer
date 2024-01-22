#include "SP/Parser/Parser.h"
#include "SP/Parser/ParserException.h"
#include "catch.hpp"

// Test the Tokenizer class
TEST_CASE("Parse if statements", "[ifParser]") {
    SECTION("Parsing of simple procedure with if statement") {
        std::string input = "Procedure p {if(x<2) then {print x;}else{print y;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 13);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::IF_THEN_ELSE);
        REQUIRE(traversalResult[4]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[7]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[8]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[9]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[10]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[11]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[12]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: IfThenElse]");
        REQUIRE(traversalResult[4]->toString() == "[<: BinaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[7]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[8]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[9]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[10]->toString() == "3: [: Print]");
        REQUIRE(traversalResult[11]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[12]->toString() == "[y: Variable]");
    }

    SECTION("Parsing of if stmt with unary '!' operator") {
        std::string input = "Procedure p {if(!(x<2)) then {print x;}else{print y;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 14);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::IF_THEN_ELSE);
        REQUIRE(traversalResult[4]->getType() == NodeType::UNARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[7]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[8]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[9]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[10]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[11]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[12]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[13]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: IfThenElse]");
        REQUIRE(traversalResult[4]->toString() == "[!: UnaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[7]->toString() == "[<: BinaryExpression]");
        REQUIRE(traversalResult[8]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[9]->toString() == "3: [: Print]");
        REQUIRE(traversalResult[10]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[11]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[12]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[13]->toString() == "[y: Variable]");
    }

    SECTION("Use of single equal instead of double") {
        std::string input = "Procedure p {if(x>(2 + 3 - r)) then {print x;} else {print y;}}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();
        auto traversalResult = root->breadthFirstTraversal();

        // REQUIRE_THROWS_AS(parser3.parseProgram(), ParserException);
    }
}

TEST_CASE("Parse invalid if expressions", "[ifParser]") {
    SECTION("Incorrect ordering of if condition") {
        std::string input = "Procedure p {if(x<>2 5) then {print x;}else {print y;}}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);

        std::string input2 = "Procedure p {if(x==0(||)y==2)then{print x;}else {print y;}}";
        Tokenizer tokenizer2 = Tokenizer(input2);
        Parser parser2 = Parser(tokenizer2);
        REQUIRE_THROWS_AS(parser2.parseProgram(), ParserException);
    }

    SECTION("Use of single equal instead of double") {
        std::string input = "Procedure p {if(x=2) then{print x;}else {print y;}}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("No cond operator found") {
        std::string input = "Procedure p {if(x+2) then{print x;}else {print y;}}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("Empty stmt lst in if block") {
        std::string input = "Procedure p {if(x+2>r) then{}else {print y;}}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
        // REQUIRE_THROWS_AS(parser4.parseProgram(), ParserException);
    }
}