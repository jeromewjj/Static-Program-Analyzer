#pragma once
#include <vector>

#include "Token.h"
using namespace std;

class Tokenizer {
public:
    Tokenizer(const string& inputString);

    // Returns next token in tokens array
    // if end of array returns empty token
    Token getNextToken();
    Token peekNextToken();
    Token getCurrToken();

private:
    vector<Token> tokens;
    int currTokenIdx;

    vector<string> split(const string& input);
    vector<Token> tokenize(const string& sourceCode);
    Token createToken(const string& tokenAsString);
    TokenType getTokenType(const string& tokenAsString);

    static bool isInteger(const std::string& str);
    static bool isAlphaNum(const string& str);
};