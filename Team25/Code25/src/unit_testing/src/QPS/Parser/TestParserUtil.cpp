#include "QPS/Parser/ParserUtil.h"
#include "catch.hpp"

TEST_CASE("Trim String") {
    SECTION("No Spaces") {
        string query = "hello";

        REQUIRE(trim(query) == "hello");
    }

    SECTION("Spaces In Front Of String") {
        string query = " hello";

        REQUIRE(trim(query) == "hello");
    }

    SECTION("Spaces Behind Of String") {
        string query = "hello ";

        REQUIRE(trim(query) == "hello");
    }
}

TEST_CASE("Split String") {
    SECTION("By Given Character") {
        string query = "hello,welcome,to,the,dark,side";

        std::vector<std::string> result = split(query, ',');
        std::vector<std::string> expectedResult = {"hello", "welcome", "to", "the", "dark", "side"};

        int i = 0;
        for (auto& splitString : result) {
            REQUIRE(splitString == expectedResult[i]);
            i += 1;
        }
    }

    SECTION("Empty String") {
        string query = "";

        std::vector<std::string> result = split(query, ',');

        REQUIRE(result.empty());
    }

    SECTION("No Given Character in String") {
        string query = "hello welcome to the dark side";

        std::vector<std::string> result = split(query, ',');

        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == "hello welcome to the dark side");
    }

    SECTION("Delimeter At Start And End") {
        string query = ",hello,welcome,to,the,dark,side,";

        std::vector<std::string> result = split(query, ',');
        std::vector<std::string> expectedResult = {"hello", "welcome", "to", "the", "dark", "side"};

        int i = 0;
        for (auto& splitString : result) {
            REQUIRE(splitString == expectedResult[i]);
            i += 1;
        }
    }

    SECTION("Delimeter In The Middle") {
        string query = "hello,welcome,,to,,the,dark,,side";

        std::vector<std::string> result = split(query, ',');
        std::vector<std::string> expectedResult = {"hello", "welcome", "to", "the", "dark", "side"};

        int i = 0;
        for (auto& splitString : result) {
            REQUIRE(splitString == expectedResult[i]);
            i += 1;
        }
    }
}

TEST_CASE("Get single term") {
    REQUIRE(getSingleTerm("x") == "x");
    REQUIRE(getSingleTerm("1") == "1");
    REQUIRE(getSingleTerm("(((x)))") == "x");
    REQUIRE(getSingleTerm("(((1)))") == "1");
    REQUIRE_THROWS(getSingleTerm("((()x)))"));
    REQUIRE_THROWS(getSingleTerm("((()))"));
    REQUIRE_THROWS(getSingleTerm(""));
    REQUIRE_THROWS(getSingleTerm("()()x"));
}

TEST_CASE("parseExpression") {
    SECTION("Valid expressions") {
        SECTION("1 operator") {
            // Plus
            std::string expr = "x + y";
            REQUIRE(*parseExpression(expr) == "((x)+(y))");
            // Minus
            expr = "x - y";
            REQUIRE(*parseExpression(expr) == "((x)-(y))");
            // Multiply
            expr = "x * y";
            REQUIRE(*parseExpression(expr) == "((x)*(y))");
            // Divide
            expr = "x / y";
            REQUIRE(*parseExpression(expr) == "((x)/(y))");
            // Mod
            expr = "x % y";
            REQUIRE(*parseExpression(expr) == "((x)%(y))");
        }

        SECTION("Multiple operators") {
            std::string expr = "a + b - c";
            REQUIRE(*parseExpression(expr) == "(((a)+(b))-(c))");
        }

        SECTION("Operators with different precedence") {
            std::string expr = "a + b * c";
            REQUIRE(*parseExpression(expr) == "((a)+((b)*(c)))");
        }

        SECTION("Operators with parentheses") {
            std::string expr = "(a + b) * c";
            REQUIRE(*parseExpression(expr) == "(((a)+(b))*(c))");
        }

        SECTION("Variable operands") {
            std::string expr = "var1 + 50";
            REQUIRE(*parseExpression(expr) == "((var1)+(50))");
        }
    }

    SECTION("Invalid expressions") {
        SECTION("Incomplete bracket") {
            std::string expr = "a + (b * c))";
            REQUIRE_THROWS(*parseExpression(expr));
        }
    }
}

TEST_CASE("Split by string") {
    SECTION("Valid Split") {
        string query = "hello and welcome";

        std::vector<std::string> result = splitStr(query, "and");
        std::vector<std::string> expectedResult = {"hello", "welcome"};

        int i = 0;
        for (auto& splitString : result) {
            REQUIRE(splitString == expectedResult[i]);
            i += 1;
        }
    }

    SECTION("Valid Split with no spaces between strDelimeter") {
        string query = "helloandwelcome";

        std::vector<std::string> result = splitStr(query, "and");
        std::vector<std::string> expectedResult = {"hello", "welcome"};

        int i = 0;
        for (auto& splitString : result) {
            REQUIRE(splitString == expectedResult[i]);
            i += 1;
        }
    }

    SECTION("Valid Split with multiple strDelimeters") {
        string query = "hello and welcomeandyou'rewelcome";

        std::vector<std::string> result = splitStr(query, "and");
        std::vector<std::string> expectedResult = {"hello", "welcome", "you'rewelcome"};

        int i = 0;
        for (auto& splitString : result) {
            REQUIRE(splitString == expectedResult[i]);
            i += 1;
        }
    }

    SECTION("No Given String in String") {
        string query = "hello welcome to the dark side";

        std::vector<std::string> result = splitStr(query, "and");

        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == "hello welcome to the dark side");
    }
}