//
// Created by Shezad Hassan on 6/9/23.
//
#include <vector>

#include "QpsToken.h"
using namespace std;
using namespace Qps;

class QpsTokenizer {
public:
    QpsTokenizer(const string& inputString);

    // Disables copy constructor
    QpsTokenizer(const QpsTokenizer&) = delete;
    QpsTokenizer& operator=(const QpsTokenizer&) = delete;

    // Enables move constructor
    QpsTokenizer(QpsTokenizer&&) = default;
    QpsTokenizer& operator=(QpsTokenizer&&) = default;

    // Returns next token in tokens array. Returns empty token at end of array.
    QpsToken getNextToken();

    QpsToken peekNextToken();

    vector<QpsToken> tokenize(const string& queryInput);

private:
    vector<QpsToken> tokens;

    int currTokenIdx;

    vector<string> split(const string& input);

    QpsToken createToken(const string& tokenAsString);

    QpsTokenType determineTokenType(const std::string& tokenAsString);

    bool isInteger(const std::string& str);

    bool isValidAlpha(const std::string& str);
};