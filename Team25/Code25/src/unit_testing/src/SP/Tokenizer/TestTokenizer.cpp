#include "SP/Tokenizer/Tokenizer.h"
#include "catch.hpp"
#include "iostream"

void testTokenization(const std::string& input, const std::vector<std::string>& expectedValues,
                      const std::vector<TokenType>& expectedTypes) {
    Tokenizer tokenizer(input);

    int i = 0;
    while (true) {
        Token token = tokenizer.getNextToken();
        if (token.getType() == EMPTY) {
            break;
        }

        // Compare token values and types with the expected values
        REQUIRE(token.getValue() == expectedValues[i]);
        REQUIRE(token.getType() == expectedTypes[i]);

        i += 1;
    }
}

// Test the Tokenizer class
TEST_CASE("Tokenize input string", "[Tokenizer]") {
    SECTION("Simple tokenization") {
        std::string input = "Procedure p {read2 = 2;}";
        std::vector<std::string> expectedTokenVals = {"Procedure", "p", "{", "read2", "=", "2", ";", "}"};
        std::vector<TokenType> expectedTokenTypes = {ALPHANUM,     ALPHANUM, LEFT_CURLY, ALPHANUM,
                                                     SINGLE_EQUAL, CONST,    SEMICOLON,  RIGHT_CURLY};

        testTokenization(input, expectedTokenVals, expectedTokenTypes);

        std::string input2 = "Procedure p1 \n\n\n\n{while(x==234){read b;}}";
        std::vector<std::string> expectedTokenVals2 = {"Procedure", "p1", "{",    "while", "(", "x", "==", "234",
                                                       ")",         "{",  "read", "b",     ";", "}", "}"};
        std::vector<TokenType> expectedTokenTypes2 = {
            ALPHANUM,          ALPHANUM,   LEFT_CURLY, ALPHANUM, LEFT_PARENTHESIS, ALPHANUM,    DOUBLE_EQUAL, CONST,
            RIGHT_PARENTHESIS, LEFT_CURLY, ALPHANUM,   ALPHANUM, SEMICOLON,        RIGHT_CURLY, RIGHT_CURLY};

        testTokenization(input2, expectedTokenVals2, expectedTokenTypes2);

        std::string input3 = "alphanum ; { } ( ) || == ! 20 02 s20 > >= < <= % + - && ";
        std::vector<std::string> expectedTokenVals3 = {"alphanum", ";", "{",  "}", "(", ")",   "||",
                                                       "==",       "!", "20", "0", "2", "s20", ">",
                                                       ">=",       "<", "<=", "%", "+", "-",   "&&"};
        std::vector<TokenType> expectedTokenTypes3 = {ALPHANUM,
                                                      SEMICOLON,
                                                      LEFT_CURLY,
                                                      RIGHT_CURLY,
                                                      LEFT_PARENTHESIS,
                                                      RIGHT_PARENTHESIS,
                                                      OR,
                                                      DOUBLE_EQUAL,
                                                      NOT,
                                                      CONST,
                                                      CONST,
                                                      CONST,
                                                      ALPHANUM,
                                                      MORE_THAN,
                                                      MORE_THAN_EQUAL,
                                                      LESS_THAN,
                                                      LESS_THAN_EQUAL,
                                                      MOD,
                                                      PLUS,
                                                      MINUS,
                                                      AND};

        testTokenization(input3, expectedTokenVals3, expectedTokenTypes3);
    }

    SECTION("Error catching") {
        std::string input = "Procedure @";
        std::vector<std::string> expectedTokenVals = {"Procedure"};
        std::vector<TokenType> expectedTokenTypes = {ALPHANUM};

        REQUIRE_THROWS_AS(testTokenization(input, expectedTokenVals, expectedTokenTypes), std::runtime_error);

        std::string input2 = "Procedure #";
        std::vector<std::string> expectedTokenVals2 = {"Procedure"};
        std::vector<TokenType> expectedTokenTypes2 = {ALPHANUM};

        REQUIRE_THROWS_AS(testTokenization(input2, expectedTokenVals2, expectedTokenTypes2), std::runtime_error);
    }

    // Add more test cases as needed...
}
