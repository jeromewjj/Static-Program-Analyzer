#include "SP/Parser/Parser.h"
#include "SP/Parser/ParserException.h"
#include "catch.hpp"

// Test the Tokenizer class
TEST_CASE("Parse source program", "[Parser]") {
    SECTION("Simple parsing of print, read, call stmts") {
        std::string input = R"(
            Procedure p {
                print x;
                read y;
                call p2;
            }
        )";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 8);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[4]->getType() == NodeType::READ);
        REQUIRE(traversalResult[5]->getType() == NodeType::CALL);
        REQUIRE(traversalResult[6]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[7]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: Print]");
        REQUIRE(traversalResult[4]->toString() == "2: [: Read]");
        REQUIRE(traversalResult[5]->toString() == "3: [p2: Call]");
        REQUIRE(traversalResult[6]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[7]->toString() == "[y: Variable]");
    }

    SECTION("Simple parsing of two procedures") {
        std::string input = "Procedure p {print x;} Procedure p2 {call p1;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 8);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[3]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[4]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[5]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[6]->getType() == NodeType::CALL);
        REQUIRE(traversalResult[7]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[p2: Procedure]");
        REQUIRE(traversalResult[3]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[4]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[5]->toString() == "1: [: Print]");
        REQUIRE(traversalResult[6]->toString() == "2: [p1: Call]");
        REQUIRE(traversalResult[7]->toString() == "[x: Variable]");
    }

    SECTION("Small program - read, if, while") {
        std::string input =
            "Procedure p {read x;while (x < 0) { read x; }read y;if (y < 0) then {print y;} else {print x;}}";
        // Simple Program:
        // Procedure p {
        //   read x;
        //   while (x < 0) { read x; }
        //
        //   read y;
        //   if (y < 0) then {
        //     print y;
        //   } else {
        //     print x;
        //   }
        // }
        // TREE:
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

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

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

    SECTION("Simple parsing of three procedures") {
        std::string input = "Procedure p {print x;read y;} Procedure p2 {call p1;}Procedure p3 {call p2;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 13);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[3]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[4]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[7]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[8]->getType() == NodeType::READ);
        REQUIRE(traversalResult[9]->getType() == NodeType::CALL);
        REQUIRE(traversalResult[10]->getType() == NodeType::CALL);
        REQUIRE(traversalResult[11]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[12]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[p2: Procedure]");
        REQUIRE(traversalResult[3]->toString() == "[p3: Procedure]");
        REQUIRE(traversalResult[4]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[7]->toString() == "1: [: Print]");
        REQUIRE(traversalResult[8]->toString() == "2: [: Read]");
        REQUIRE(traversalResult[9]->toString() == "3: [p1: Call]");
        REQUIRE(traversalResult[10]->toString() == "4: [p2: Call]");
        REQUIRE(traversalResult[11]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[12]->toString() == "[y: Variable]");
    }

    SECTION("simple expression with plus and minus") {
        std::string input = "procedure A {x = x + y - 10;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();
        auto traversalResult = root->breadthFirstTraversal();
    }

    SECTION("simple expression with plus and minus") {
        std::string input = "procedure A {x = x * y / 10 + 2 % s;}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();
        auto traversalResult = root->breadthFirstTraversal();
    }

    SECTION("Long procedure") {
        std::string input = "procedure A {\n"
                            "    read x;\n"
                            "    read y;\n"
                            "    print y;\n"
                            "    while (x > y) {\n"
                            "        if (x > 0) then {\n"
                            "            y = y + y;\n"
                            "        } else {\n"
                            "            x = x - 1;\n"
                            "        }\n"
                            "\n"
                            "        while (x == 1) {\n"
                            "            y = 5 + y;\n"
                            "            x = x + y - 10;\n"
                            "        }\n"
                            "    }\n"
                            "}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();
        auto traversalResult = root->breadthFirstTraversal();
    }
}

TEST_CASE("Parse invalid source program", "[Parser]") {
    SECTION("Missing closing bracket") {
        std::string input = "Procedure p {print x;read y; call p2;";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("Missing variable") {
        std::string input = "Procedure p {print ;read y; call p2;}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("Invalid variable name") {
        std::string input = "Procedure p {print x\n"
                            ";read 2y; call p2;}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("Empty statement list") {
        std::string input = "procedure A {}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }
}