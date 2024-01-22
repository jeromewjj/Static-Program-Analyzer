//
// Created by Shezad Hassan on 6/9/23.
//

#include "QPS/Tokenizer/QpsTokenizer.h"
#include "catch.hpp"
#include "iostream"

// Test the Tokenizer class
void testQpsTokenization(const std::string& input, const std::vector<std::string>& expectedValues,
                         const std::vector<QpsTokenType>& expectedTypes) {
    QpsTokenizer tokenizer(input);

    int i = 0;
    while (true) {
        QpsToken token = tokenizer.getNextToken();
        if (token.getType() == EMPTY) {
            break;
        }

        // Compare token values and types with the expected values
        REQUIRE(token.getValue() == expectedValues[i]);
        REQUIRE(token.getType() == expectedTypes[i]);

        i += 1;
    }
}

TEST_CASE("Tokenize query string", "[Tokenizer]") {
    SECTION("Tokenization of valid query") {
        std::string input = "variable v; Select v";
        std::vector<std::string> expectedTokenVals = {"variable", "v", ";", "Select", "v"};
        std::vector<QpsTokenType> expectedTokenTypes = {ALPHANUM, ALPHANUM, SEMICOLON, ALPHANUM, ALPHANUM};

        testQpsTokenization(input, expectedTokenVals, expectedTokenTypes);
    }

    SECTION("Tokenization of valid query with Expression") {
        std::string input = "assign a; Select a pattern a(\"normSq\", _\"cenX * cenX\"_)";
        std::vector<std::string> expectedTokenVals = {"assign", "a", ";",          "Select", "a", "pattern",
                                                      "a",      "(", "\"normSq\"", ",",      "_", "\"cenX * cenX\"",
                                                      "_",      ")"};
        std::vector<QpsTokenType> expectedTokenTypes = {
            ALPHANUM,         ALPHANUM, SEMICOLON, ALPHANUM,   ALPHANUM, ALPHANUM,   ALPHANUM,
            LEFT_PARENTHESIS, ALPHANUM, COMMA,     UNDERSCORE, ALPHANUM, UNDERSCORE, RIGHT_PARENTHESIS};

        testQpsTokenization(input, expectedTokenVals, expectedTokenTypes);
    }
}
