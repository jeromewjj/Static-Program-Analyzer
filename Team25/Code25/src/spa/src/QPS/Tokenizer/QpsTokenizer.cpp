//
// Created by Shezad Hassan on 6/9/23.
//

#include "QpsTokenizer.h"

#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const unordered_map<string, QpsTokenType> QPS_TOKEN_TYPES = {
    {"(", LEFT_PARENTHESIS},
    {")", RIGHT_PARENTHESIS},
    {";", SEMICOLON},
    {",", COMMA},
    {"and", AND},
    {"not", NOT},
    {"with", WITH},
    {"_", UNDERSCORE},
    {"<", TUPLE_OPEN_BRACKET},
    {">", TUPLE_CLOSE_BRACKET},
    {"=", EQUALS},
    {".", DOT},
    {"#", HASH},
};

QpsTokenizer::QpsTokenizer(const string& inputString) {
    currTokenIdx = -1;
};

QpsToken QpsTokenizer::getNextToken() {
    currTokenIdx += 1;
    if (currTokenIdx == tokens.size()) {
        return QpsToken("", EMPTY);
    }
    return tokens[currTokenIdx];
}

QpsToken QpsTokenizer::peekNextToken() {
    if (currTokenIdx + 1 == tokens.size()) {
        return QpsToken("", EMPTY);
    }
    return tokens[currTokenIdx + 1];
}

vector<QpsToken> QpsTokenizer::tokenize(const string& queryInput) {
    // Split source into an array of strings
    vector<string> tokens_as_strings = split(queryInput);

    // Loop through strings to create respective token objects
    vector<QpsToken> tokens;
    for (const string& str : tokens_as_strings) {
        QpsToken token = createToken(str);
        tokens.push_back(token);
    }

    return tokens;
}

// Splits input string into an array of tokens represented as string
vector<string> QpsTokenizer::split(const string& input) {
    vector<string> tokens;

    regex pattern(
        "([a-zA-Z][[:alnum:]]*)|(0|[1-9][0-9]*)|(==)|(>=)|(<=)|(&&)|(\\|\\|)|(?:\\\"[^\\\"]*\\\")|([[:punct:]])");
    sregex_iterator it(input.begin(), input.end(), pattern);
    sregex_iterator end;

    while (it != end) {
        smatch match = *it;
        tokens.push_back(match.str());
        ++it;
    }
    return tokens;
}

QpsToken QpsTokenizer::createToken(const string& tokenAsString) {
    QpsTokenType type = determineTokenType(tokenAsString); // Implement your logic to determine the token type
    return QpsToken(tokenAsString, type);
}

QpsTokenType QpsTokenizer::determineTokenType(const string& tokenAsString) {
    auto it = QPS_TOKEN_TYPES.find(tokenAsString);
    if (it != QPS_TOKEN_TYPES.end()) {
        return it->second;
    }

    if (isInteger(tokenAsString)) {
        return CONST;
    }

    return ALPHANUM;
}

bool QpsTokenizer::isInteger(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false; // Not a valid integer
        }
    }
    return !str.empty(); // Empty string is not a valid integer
}

bool QpsTokenizer::isValidAlpha(const string& str) {
    if (str.empty()) {
        return false; // Empty string, cannot start with a letter
    }

    if (!std::isalpha(str[0])) {
        return false; // First character is not a letter
    }

    for (size_t i = 1; i < str.length(); ++i) {
        if (!std::isalnum(str[i])) {
            return false; // Found a non-alphanumeric character
        }
    }

    return true; // String is alphanumeric and starts with a letter
}