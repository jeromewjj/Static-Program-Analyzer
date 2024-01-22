#include "ParserUtil.h"

#include "QPS/QPSException/SyntacticException.h"

std::string trim(const std::string& s) {
    // Find the first non-whitespace character
    size_t first = s.find_first_not_of(Constants::WHITESPACE);

    // If the string is empty or contains only whitespace
    if (first == std::string::npos) {
        return s;
    }

    // Find the last non-whitespace character
    size_t last = s.find_last_not_of(Constants::WHITESPACE);

    // Return the trimmed string
    return s.substr(first, (last - first + 1));
}

std::vector<std::string> split(const string& str, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        std::string token = str.substr(start, end - start);
        token = trim(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        start = end + 1;
        end = str.find(delimiter, start);
    }

    std::string lastToken = str.substr(start, end);
    lastToken = trim(lastToken);
    if (!lastToken.empty()) {
        tokens.push_back(lastToken);
    }

    return tokens;
}

// stopgap measure til can parse expression properly
// milestone 1 only requires single term paran and whitespace
std::string getSingleTerm(std::string parenthesizedSingleTerm) {
    parenthesizedSingleTerm.erase(
        std::remove_if(parenthesizedSingleTerm.begin(), parenthesizedSingleTerm.end(), ::isspace),
        parenthesizedSingleTerm.end());

    int n = parenthesizedSingleTerm.length();

    int numOfBracketPairs = 0;
    int i = 0;
    for (char c : parenthesizedSingleTerm) {
        if (c == '(') {
            ++numOfBracketPairs;
        }
        else {
            break;
        }
    }

    int lenOfTerm = n - 2 * numOfBracketPairs;
    if (lenOfTerm <= 0) {
        throw SyntacticException("Invalid expression input: ");
    }

    std::string singleTerm = parenthesizedSingleTerm.substr(numOfBracketPairs, lenOfTerm);
    for (char c : singleTerm) {
        if (c == '(' or c == ')') {
            throw SyntacticException("invalid expression input: ");
        }
    }

    std::string closingBrackets = parenthesizedSingleTerm.substr(n - numOfBracketPairs);
    for (char c : closingBrackets) {
        if (c != ')') {
            throw SyntacticException("invalid expression input: ");
        }
    }

    return singleTerm;
}

// This method abstracts the process of removing all the brackets and adding the brackets like SP
std::shared_ptr<string> parseExpression(std::string& expr) {
    // Tokenize expr
    Tokenizer tokenizer{expr};
    // infixToPostfix(Tokenizer)
    shared_ptr<vector<Token>> postFixTokens = infixToPostfix(tokenizer);
    // addExprBrackets(expr)
    return addExprBrackets(postFixTokens);
}

// Adds brackets to the exprSpec, similar to SP
std::shared_ptr<string> addExprBrackets(const shared_ptr<vector<Token>>& postFixTokens) {
    stack<std::shared_ptr<string>> operandStack;

    for (Token& token : *postFixTokens) {
        if (token.getType() == ALPHANUM or token.getType() == CONST) {
            std::shared_ptr<string> bracketedExpression = make_shared<string>("(" + token.getValue() + ")");
            operandStack.push(bracketedExpression);
        }
        else if (isValidTokenType(token)) {
            if (operandStack.size() < 2) {
                throw runtime_error("QPS Expression Parser: Insufficient operands for operator.");
            }
            std::shared_ptr<string> rightOperand = operandStack.top();
            operandStack.pop();
            std::shared_ptr<string> leftOperand = operandStack.top();
            operandStack.pop();

            std::shared_ptr<string> operatorNode =
                make_shared<string>("(" + *leftOperand + token.getValue() + *rightOperand + ")");
            operandStack.push(operatorNode);
        }
    }

    // After processing all tokens, the operand stack should contain the root of the AST
    if (operandStack.size() != 1) {
        throw runtime_error("Invalid expression.");
    }
    return operandStack.top();
}

shared_ptr<vector<Token>> infixToPostfix(Tokenizer& tokenizer) {
    stack<Token> operators;
    shared_ptr<vector<Token>> postfixTokens = make_shared<vector<Token>>();

    while (true) {
        Token token = tokenizer.getNextToken();
        TokenType tokenType = token.getType();

        if (tokenType == TokenType::EMPTY) {
            break;
        }

        if (tokenType == TokenType::CONST or tokenType == TokenType::ALPHANUM) {
            postfixTokens->push_back(token);
        }
        else if (tokenType == TokenType::LEFT_PARENTHESIS) {
            operators.push(token);
        }
        else if (tokenType == TokenType::RIGHT_PARENTHESIS) {
            // If token is a closing parenthesis, pop operators from the stack
            // and add them to the postfix expression until an opening parenthesis is encountered
            while (!operators.empty() && operators.top().getType() != TokenType::LEFT_PARENTHESIS) {
                postfixTokens->push_back(operators.top());
                operators.pop();
            }
            if (operators.empty())
                throw runtime_error("Unmatched parentheses in expression!");
            // Pop the opening parenthesis from the stack
            operators.pop();
        }
        else if (isValidTokenType(token)) {
            // If token is an operator, pop operators from the stack and add them to
            // the postfix expression as long as they have higher or equal precedence
            while (!operators.empty() && operators.top().getType() != TokenType::LEFT_PARENTHESIS &&
                   precedence(operators.top().getType()) >= precedence(token.getType())) {
                postfixTokens->push_back(operators.top());
                operators.pop();
            }
            // Push the current operator onto the stack
            operators.push(token);
        }
    }
    // Pop any remaining operators from the stack and add them to the postfix expression
    while (!operators.empty()) {
        postfixTokens->push_back(operators.top());
        operators.pop();
    }
    return postfixTokens;
}

int precedence(TokenType type) {
    switch (type) {
    case PLUS:
    case MINUS:
        return 1;
    case MULTIPLY:
    case DIVIDE:
    case MOD:
        return 2;
    default:
        return 0;
    }
}

bool isValidTokenType(Token& token) {
    if (token.getType() == PLUS || token.getType() == MINUS || token.getType() == MULTIPLY ||
        token.getType() == DIVIDE || token.getType() == MOD) {
        return true;
    }
    return false;
}

std::vector<std::string> splitStr(const std::string& str, std::string strDelimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(strDelimiter);

    while (end != std::string::npos) {
        std::string token = str.substr(start, end - start);
        token = trim(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        start = end + strDelimiter.length();
        end = str.find(strDelimiter, start);
    }

    std::string lastToken = str.substr(start, end);
    lastToken = trim(lastToken);
    if (!lastToken.empty()) {
        tokens.push_back(lastToken);
    }

    return tokens;
}
