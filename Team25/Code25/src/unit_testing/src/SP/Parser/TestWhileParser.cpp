#include "SP/Parser/Parser.h"
#include "SP/Parser/ParserException.h"
#include "catch.hpp"

// Test the Tokenizer class
TEST_CASE("Parse while statements", "[whileParser]") {
    SECTION("Parsing of simple procedure with while statement") {
        std::string input = "Procedure p {while(x<2){print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 10);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[4]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[7]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[8]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[9]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: WhileThen]");
        REQUIRE(traversalResult[4]->toString() == "[<: BinaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[7]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[8]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[9]->toString() == "[x: Variable]");
    }

    SECTION("Parsing of while stmt with unary '!' operator") {
        std::string input = "Procedure p {while(!(x<2)){print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 11);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[4]->getType() == NodeType::UNARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[7]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[8]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[9]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[10]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: WhileThen]");
        REQUIRE(traversalResult[4]->toString() == "[!: UnaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[<: BinaryExpression]");
        REQUIRE(traversalResult[7]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[8]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[9]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[10]->toString() == "[x: Variable]");
    }

    SECTION("Parsing of while stmt with unary '&&' operator") {
        std::string input = "Procedure p {while((x != 0) && (y != 0)) { print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();
    }

    SECTION("Parsing of while stmt with unary '||' operator") {
        std::string input = "Procedure p {while (1>= 1%((1)) ) { print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 12);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[4]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[7]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[8]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[9]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[10]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[11]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: WhileThen]");
        REQUIRE(traversalResult[4]->toString() == "[>=: BinaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[1: Constant]");
        REQUIRE(traversalResult[7]->toString() == "[%: BinaryExpression]");
        REQUIRE(traversalResult[8]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[9]->toString() == "[1: Constant]");
        REQUIRE(traversalResult[10]->toString() == "[1: Constant]");
        REQUIRE(traversalResult[11]->toString() == "[x: Variable]");
    }

    SECTION("Parsing of while stmt with unary '||' operator") {
        std::string input = "Procedure p {while (1>= 1%((0-1)) ) { print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 14);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[4]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[7]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[8]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[9]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[10]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[11]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[12]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[13]->getType() == NodeType::CONSTANT);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: WhileThen]");
        REQUIRE(traversalResult[4]->toString() == "[>=: BinaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[1: Constant]");
        REQUIRE(traversalResult[7]->toString() == "[%: BinaryExpression]");
        REQUIRE(traversalResult[8]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[9]->toString() == "[1: Constant]");
        REQUIRE(traversalResult[10]->toString() == "[-: BinaryExpression]");
        REQUIRE(traversalResult[11]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[12]->toString() == "[0: Constant]");
        REQUIRE(traversalResult[13]->toString() == "[1: Constant]");
    }

    SECTION("Parsing of while stmt with unary '||' operator") {
        std::string input = "Procedure p {while (x<=(0+0)) { print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 12);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[4]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[7]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[8]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[9]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[10]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[11]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: WhileThen]");
        REQUIRE(traversalResult[4]->toString() == "[<=: BinaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[7]->toString() == "[+: BinaryExpression]");
        REQUIRE(traversalResult[8]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[9]->toString() == "[0: Constant]");
        REQUIRE(traversalResult[10]->toString() == "[0: Constant]");
        REQUIRE(traversalResult[11]->toString() == "[x: Variable]");
    }

    SECTION("Parsing of while stmt with unary '||' operator") {
        std::string input = "Procedure p {while( !(x<2+(5*y))) { print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        /*
        cout << traversalResult[1]->toString() << endl;
        cout << traversalResult[2]->toString() << endl;
        cout << traversalResult[3]->toString() << endl;
        cout << traversalResult[4]->toString() << endl;
        cout << traversalResult[5]->toString() << endl;
        cout << traversalResult[6]->toString() << endl;
        cout << traversalResult[7]->toString() << endl;
        cout << traversalResult[8]->toString() << endl;
        cout << traversalResult[9]->toString() << endl;
        cout << traversalResult[10]->toString() << endl;
        cout << traversalResult[11]->toString() << endl;
        cout << traversalResult[12]->toString() << endl;
        cout << traversalResult[13]->toString() << endl;
        */
        REQUIRE(traversalResult.size() == 15);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[4]->getType() == NodeType::UNARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[7]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[8]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[9]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[10]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[11]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[12]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[13]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[14]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: WhileThen]");
        REQUIRE(traversalResult[4]->toString() == "[!: UnaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[<: BinaryExpression]");
        REQUIRE(traversalResult[7]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[8]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[9]->toString() == "[+: BinaryExpression]");
        REQUIRE(traversalResult[10]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[11]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[12]->toString() == "[*: BinaryExpression]");
        REQUIRE(traversalResult[13]->toString() == "[5: Constant]");
        REQUIRE(traversalResult[14]->toString() == "[y: Variable]");
    }

    SECTION("Parsing of while stmt with unary '||' operator") {
        std::string input = "Procedure p {while( (!(x==2+(5%y))) || (y!=(2*5+y))) { print x;}}";

        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        ASTNodePtr root = parser.parseProgram();

        auto traversalResult = root->breadthFirstTraversal();

        REQUIRE(traversalResult.size() == 23);
        REQUIRE(traversalResult[0]->getType() == NodeType::PROGRAM);
        REQUIRE(traversalResult[1]->getType() == NodeType::PROCEDURE);
        REQUIRE(traversalResult[2]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[3]->getType() == NodeType::WHILE_THEN);
        REQUIRE(traversalResult[4]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[5]->getType() == NodeType::STMT_LIST);
        REQUIRE(traversalResult[6]->getType() == NodeType::UNARY_EXPRESSION);
        REQUIRE(traversalResult[7]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[8]->getType() == NodeType::PRINT);
        REQUIRE(traversalResult[9]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[10]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[11]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[12]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[13]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[14]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[15]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[16]->getType() == NodeType::VARIABLE);
        REQUIRE(traversalResult[17]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[18]->getType() == NodeType::BINARY_EXPRESSION);
        REQUIRE(traversalResult[19]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[20]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[21]->getType() == NodeType::CONSTANT);
        REQUIRE(traversalResult[22]->getType() == NodeType::VARIABLE);

        // Test string representation
        REQUIRE(traversalResult[0]->toString() == "[main: Program]");
        REQUIRE(traversalResult[1]->toString() == "[p: Procedure]");
        REQUIRE(traversalResult[2]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[3]->toString() == "1: [: WhileThen]");
        REQUIRE(traversalResult[4]->toString() == "[||: BinaryExpression]");
        REQUIRE(traversalResult[5]->toString() == "[: StmtList]");
        REQUIRE(traversalResult[6]->toString() == "[!: UnaryExpression]");
        REQUIRE(traversalResult[7]->toString() == "[!=: BinaryExpression]");
        REQUIRE(traversalResult[8]->toString() == "2: [: Print]");
        REQUIRE(traversalResult[9]->toString() == "[==: BinaryExpression]");
        REQUIRE(traversalResult[10]->toString() == "[y: Variable]");
        REQUIRE(traversalResult[11]->toString() == "[+: BinaryExpression]");
        REQUIRE(traversalResult[12]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[13]->toString() == "[x: Variable]");
        REQUIRE(traversalResult[14]->toString() == "[+: BinaryExpression]");
        REQUIRE(traversalResult[15]->toString() == "[*: BinaryExpression]");
        REQUIRE(traversalResult[16]->toString() == "[y: Variable]");
        REQUIRE(traversalResult[17]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[18]->toString() == "[%: BinaryExpression]");
        REQUIRE(traversalResult[19]->toString() == "[2: Constant]");
        REQUIRE(traversalResult[20]->toString() == "[5: Constant]");
        REQUIRE(traversalResult[21]->toString() == "[5: Constant]");
        REQUIRE(traversalResult[22]->toString() == "[y: Variable]");
    }
}

TEST_CASE("Parse invalid while expressions", "[whileParser]") {
    SECTION("Parentheses around operators") {
        std::string input = "Procedure p {while(x(==)0){print x;}}";
        Tokenizer tokenizer = Tokenizer(input);
        Parser parser = Parser(tokenizer);
        REQUIRE_THROWS_AS(parser.parseProgram(), ParserException);
    }

    SECTION("Incorrect ordering of cond expression") {
        std::string input2 = "Procedure p {while(x==0(||)y==2){print x;}}";
        Tokenizer tokenizer2 = Tokenizer(input2);
        Parser parser2 = Parser(tokenizer2);
        REQUIRE_THROWS_AS(parser2.parseProgram(), ParserException);

        std::string input4 = "Procedure p {while(!( <= x 2)) {print x;}}";
        Tokenizer tokenizer4 = Tokenizer(input4);
        Parser parser4 = Parser(tokenizer4);
        REQUIRE_THROWS_AS(parser4.parseProgram(), ParserException);
    }
}