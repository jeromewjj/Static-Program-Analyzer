#pragma onnce
#include "ExpressionParser.h"

class AssignmentExpressionParser : public ExpressionParser {
private:
    std::shared_ptr<Expression> postFixToTree(const shared_ptr<vector<Token>>& postFixTokens) override;

    int precedence(TokenType type) override;

    string& identifyOperatorType(Token& token) override;

    bool isValidTokenType(Token& token) override;

    void validateExpression(const shared_ptr<vector<Token>>& infixTokens) override;
};
