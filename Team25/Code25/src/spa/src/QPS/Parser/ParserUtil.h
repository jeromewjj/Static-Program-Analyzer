#include <stack>
#include <string>
#include <vector>

#include "QPS/Constants.h"
#include "SP/Tokenizer/Tokenizer.h"

using namespace std;

std::string trim(const std::string& s);
std::vector<std::string> split(const std::string& str, char delimiter);
std::string getSingleTerm(std::string parenthesizedSingleTerm);
shared_ptr<vector<Token>> infixToPostfix(Tokenizer& tokenizer);
// Expression parsing methods
std::shared_ptr<string> parseExpression(std::string& expr);
std::shared_ptr<string> addExprBrackets(const shared_ptr<vector<Token>>& postFixTokens);
int precedence(TokenType type);
bool isValidTokenType(Token& token);
std::vector<std::string> splitStr(const std::string& str, std::string strDelimiter);