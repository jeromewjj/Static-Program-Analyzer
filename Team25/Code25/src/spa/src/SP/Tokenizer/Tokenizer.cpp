#include "Tokenizer.h"

#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const unordered_map<string, TokenType> TOKEN_TYPES = {
    {"(", LEFT_PARENTHESIS},
    {")", RIGHT_PARENTHESIS},
    {"{", LEFT_CURLY},
    {"}", RIGHT_CURLY},
    {";", SEMICOLON},
    {"+", PLUS},
    {"-", MINUS},
    {"*", MULTIPLY},
    {"/", DIVIDE},
    {"%", MOD},
    {"=", SINGLE_EQUAL},
    {"==", DOUBLE_EQUAL},
    {"!", NOT},
    {"!=", NOT_EQUAL},
    {">", MORE_THAN},
    {">=", MORE_THAN_EQUAL},
    {"<", LESS_THAN},
    {"<=", LESS_THAN_EQUAL},
    {"&&", AND},
    {"||", OR},
};

Tokenizer::Tokenizer(const string& inputString) {
    tokens = tokenize(inputString);
    currTokenIdx = -1;
};

Token Tokenizer::getNextToken() {
    currTokenIdx += 1;
    if (currTokenIdx >= tokens.size()) {
        return {"", EMPTY};
    }
    return tokens[currTokenIdx];
}

Token Tokenizer::peekNextToken() {
    int nextIdx = currTokenIdx + 1;
    if (nextIdx >= tokens.size()) {
        return {"", EMPTY};
    }
    return tokens[nextIdx];
}

Token Tokenizer::getCurrToken() {
    if (currTokenIdx >= tokens.size()) {
        return {"", EMPTY};
    }
    return tokens[currTokenIdx];
}

vector<Token> Tokenizer::tokenize(const string& sourceCode) {
    // split source into an array of strings
    vector<string> tokensAsStrings = split(sourceCode);

    // loop through strings to create respective token objects
    vector<Token> tokens;
    for (const string& str : tokensAsStrings) {
        Token token = createToken(str);
        tokens.push_back(token);
    }

    return tokens;
}

// Splits input string into an array of tokens represented as string
vector<string> Tokenizer::split(const string& input) {
    vector<string> tokens;

    regex pattern("([a-zA-Z][[:alnum:]]*)|(0|[1-9][0-9]*)|(!=)|(==)|(>=)|(<=)|(&&)|(\\|\\|)|([[:punct:]])");
    sregex_iterator it(input.begin(), input.end(), pattern);
    sregex_iterator end;

    while (it != end) {
        smatch match = *it;
        tokens.push_back(match.str());
        ++it;
    }
    return tokens;
}

Token Tokenizer::createToken(const string& tokenAsString) {
    TokenType type = getTokenType(tokenAsString); // Implement your logic to determine the token type
    return Token(tokenAsString, type);
}

TokenType Tokenizer::getTokenType(const string& tokenAsString) {
    auto itr = TOKEN_TYPES.find(tokenAsString);
    if (itr != TOKEN_TYPES.end()) {
        return itr->second;
    }

    if (isInteger(tokenAsString)) {
        return CONST;
    }
    else if (isAlphaNum(tokenAsString)) {
        return ALPHANUM;
    }

    throw std::runtime_error("Invalid Token Detected in Tokenizer.cpp: " + tokenAsString);
}

bool Tokenizer::isInteger(const std::string& str) {
    if (str.empty())
        return false;

    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool Tokenizer::isAlphaNum(const string& str) {
    if (str.empty())
        return false; // empty string cannot start with a letter

    // first character must be a letter
    if (!std::isalpha(str[0])) {
        return false;
    }

    // subsequent characters must be alphanumeric
    for (size_t i = 1; i < str.length(); ++i) {
        if (!std::isalnum(str[i])) {
            return false;
        }
    }

    return true;
}
