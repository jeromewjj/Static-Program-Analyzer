#include "QPSGrammarUtil.h"

bool isName(std::string s) {
    return std::regex_match(trim(s), regex(Constants::NAME_PATTERN));
}

bool isIdent(std::string s) { // isName and isIdent has the same rule
    return isName(s);
}

bool isInteger(std::string s) {
    return std::regex_match(trim(s), regex(Constants::INTEGER_PATTERN));
}

bool isSynonym(std::string s) { // Synonym is Ident
    return isIdent(s);
}

bool isDesignEntity(std::string s) {
    static const std::regex validEntityPattern(Constants::ENTITY_PATTERN);
    return std::regex_match(trim(s), validEntityPattern);
}

bool isDeclaration(std::string designEntityToken, std::string synonymToken, std::string semiColonToken) {
    return isDesignEntity(designEntityToken) && isSynonym(synonymToken) && trim(semiColonToken) == Constants::SEMICOLON;
}

bool isMultiDeclaration(std::string designEntityToken, std::string synonymToken, std::string commaToken) {
    return isDesignEntity(designEntityToken) && isSynonym(synonymToken) && trim(commaToken) == Constants::COMMA;
}

bool isSelect(std::string s) {
    return trim(s) == Constants::SELECT_PATTERN;
    ;
}

bool isSuch(std::string s) {
    return trim(s) == Constants::SUCH_PATTERN;
    ;
}

bool isThat(std::string s) {
    return trim(s) == Constants::THAT_PATTERN;
}

bool isStmtRef(std::string s) {
    s = trim(s);
    return isSynonym(s) || s == Constants::UNDERSCORE || isInteger(s);
}

bool isEntRef(std::string s) {
    s = trim(s);
    return isSynonym(s) || s == Constants::UNDERSCORE ||
           (s[0] == Constants::CHAR_DOUBLE_QUOTE && isIdent(s.substr(1, s.length() - 2)) &&
            s[s.length() - 1] == Constants::CHAR_DOUBLE_QUOTE);
}

bool isFollows(std::string s) {
    auto [rel, stmtRef1, stmtRef2] = parseRef(s);
    return rel == Constants::FOLLOWS_PATTERN && isStmtRef(stmtRef1) && isStmtRef(stmtRef2);
}

bool isFollowsT(std::string s) {
    auto [rel, stmtRef1, stmtRef2] = parseRef(s);
    return rel == Constants::FOLLOWST_PATTERN && isStmtRef(stmtRef1) && isStmtRef(stmtRef2);
}

bool isParent(std::string s) {
    auto [rel, stmtRef1, stmtRef2] = parseRef(s);
    return rel == Constants::PARENT_PATTERN && isStmtRef(stmtRef1) && isStmtRef(stmtRef2);
}

bool isParentT(std::string s) {
    auto [rel, stmtRef1, stmtRef2] = parseRef(s);
    return rel == Constants::PARENTT_PATTERN && isStmtRef(stmtRef1) && isStmtRef(stmtRef2);
}

bool isUsesS(std::string s) {
    auto [rel, stmtRef, entRef] = parseRef(s);
    return rel == Constants::USES_PATTERN && isStmtRef(stmtRef) && isEntRef(entRef);
}

bool isUsesP(std::string s) {
    auto [rel, entRef1, entRef2] = parseRef(s);
    return rel == Constants::USES_PATTERN && isEntRef(entRef1) && isEntRef(entRef2);
}

bool isModifiesS(std::string s) {
    auto [rel, stmtRef, entRef] = parseRef(s);
    return rel == Constants::MODIFIES_PATTERN && isStmtRef(stmtRef) && isEntRef(entRef);
}

bool isModifiesP(std::string s) {
    auto [rel, entRef1, entRef2] = parseRef(s);
    return rel == Constants::MODIFIES_PATTERN && isEntRef(entRef1) && isEntRef(entRef2);
}

bool isCalls(std::string s) {
    auto [rel, entRef1, entRef2] = parseRef(s);
    return rel == Constants::CALLS_PATTERN && isEntRef(entRef1) && isEntRef(entRef2);
}

bool isCallsT(std::string s) {
    auto [rel, entRef1, entRef2] = parseRef(s);
    return rel == Constants::CALLST_PATTERN && isEntRef(entRef1) && isEntRef(entRef2);
}

bool isNext(std::string s) {
    auto [rel, stmtRef1, stmtRef2] = parseRef(s);
    return rel == Constants::NEXT_PATTERN && isStmtRef(stmtRef1) && isStmtRef(stmtRef2);
}

bool isNextT(std::string s) {
    auto [rel, stmtRef1, stmtRef2] = parseRef(s);
    return rel == Constants::NEXTT_PATTERN && isStmtRef(stmtRef1) && isStmtRef(stmtRef2);
}

bool isAffects(std::string s) {
    auto [rel, stmtRef1, stmtRef2] = parseRef(s);
    return rel == Constants::AFFECTS_PATTERN && isStmtRef(stmtRef1) && isStmtRef(stmtRef2);
}

bool isRelRef(std::string s) {
    return isFollows(s) || isFollowsT(s) || isParent(s) || isParentT(s) || isUsesS(s) || isUsesP(s) || isModifiesS(s) ||
           isModifiesP(s) || isCalls(s) || isCallsT(s) || isNext(s) || isNextT(s) || isAffects(s);
}

std::tuple<std::string, std::string, std::string> parseRef(std::string s) {
    size_t startParen = s.find(Constants::CHAR_OPEN_PARENTHESIS);
    size_t comma = s.find(Constants::CHAR_COMMA);
    size_t endParen = s.rfind(Constants::CHAR_CLOSE_PARENTHESIS);
    size_t extraComma = s.find(Constants::CHAR_COMMA, comma + 1);

    if (comma == std::string::npos || extraComma != std::string::npos || startParen >= comma || comma >= endParen ||
        endParen != s.length() - 1) {
        throw SyntacticException("Invalid Ref format: ");
    }

    std::string rel = s.substr(0, startParen);
    std::string ref1 = s.substr(startParen + 1, comma - startParen - 1);
    std::string ref2 = s.substr(comma + 1, endParen - comma - 1);

    return std::make_tuple(rel, ref1, ref2);
}

bool isVarName(std::string s) {
    return isName(s);
}

bool isConstValue(std::string s) {
    return isInteger(s);
}

bool isFactor(std::string s) {
    s = trim(s);

    if (s.empty()) {
        return false;
    }
    if (isVarName(s) || isConstValue(s)) {
        return true;
    }
    if (s[0] == Constants::CHAR_OPEN_PARENTHESIS && s[s.size() - 1] == Constants::CHAR_CLOSE_PARENTHESIS) {
        return isExpr(s.substr(1, s.size() - 2));
    }
    if (s.length() == 1) {
        return false;
    }
    return isExpr(s);
}

bool isTerm(std::string s) {
    s = trim(s);

    if (s.empty()) {
        return false;
    }

    int parenthesisCount = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == Constants::CHAR_OPEN_PARENTHESIS) {
            parenthesisCount++;
            continue;
        }
        if (s[i] == Constants::CHAR_CLOSE_PARENTHESIS) {
            parenthesisCount--;
            continue;
        }
        if (parenthesisCount == 0 &&
            (s[i] == Constants::CHAR_MULTIPLY || s[i] == Constants::CHAR_DIVIDE || s[i] == Constants::CHAR_MOD)) {
            return isTerm(s.substr(0, i)) && isFactor(s.substr(i + 1));
        }
    }
    return isFactor(s);
}

bool isExpr(std::string s) {
    s = trim(s);

    if (s.empty()) {
        return false;
    }

    int parenthesisCount = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == Constants::CHAR_OPEN_PARENTHESIS) {
            parenthesisCount++;
            continue;
        }
        if (s[i] == Constants::CHAR_CLOSE_PARENTHESIS) {
            parenthesisCount--;
            continue;
        }
        if (parenthesisCount == 0 && (s[i] == Constants::CHAR_PLUS || s[i] == Constants::CHAR_MINUS)) {
            return isExpr(s.substr(0, i)) && isTerm(s.substr(i + 1));
        }
    }
    return isTerm(s);
}

bool isExpressionSpec(std::string s) {
    s = trim(s);

    if (s.empty()) {
        return false;
    }

    return isQuotedExpressionSpec(s) || isWildcardQuotedExpressionSpec(s) || isUnderscore(s);
}

bool isWildcardQuotedExpressionSpec(std::string s) {
    s = trim(s);

    if (s.length() >= 4 && s[0] == Constants::CHAR_UNDERSCORE && s[s.length() - 1] == Constants::CHAR_UNDERSCORE &&
        ((s[1] == Constants::CHAR_DOUBLE_QUOTE && s[s.length() - 2] == Constants::CHAR_DOUBLE_QUOTE) ||
         (s[1] == Constants::CHAR_SINGLE_QUOTE && s[s.length() - 2] == Constants::CHAR_SINGLE_QUOTE))) {
        std::string expr = s.substr(2, s.length() - 4);
        return isExpr(expr);
    }

    return false;
}

bool isQuotedExpressionSpec(std::string s) {
    s = trim(s);

    if (s.length() >= 2 &&
        ((s[0] == Constants::CHAR_DOUBLE_QUOTE && s[s.length() - 1] == Constants::CHAR_DOUBLE_QUOTE) ||
         (s[0] == Constants::CHAR_SINGLE_QUOTE && s[s.length() - 1] == Constants::CHAR_SINGLE_QUOTE))) {
        std::string expr = s.substr(1, s.length() - 2);
        return isExpr(expr);
    }

    return false;
}

bool isPattern(std::string s) {
    return trim(s) == Constants::PATTERN_PATTERN;
    ;
}

bool isUnderscore(std::string s) {
    return trim(s) == Constants::UNDERSCORE;
}

bool isAttrName(std::string s) {
    return s == Constants::PROCNAME_PATTERN || s == Constants::VARNAME_PATTERN || s == Constants::VALUE_PATTERN ||
           s == Constants::STMTNO_PATTERN;
}

bool isAttrRef(std::string s) {
    s = trim(s);
    size_t dot = s.find(Constants::CHAR_DOT);
    if (dot == std::string::npos)
        return false;
    return isSynonym(s.substr(0, dot)) && isAttrName(s.substr(dot + 1));
}

bool isElem(std::string s) {
    return isSynonym(s) || isAttrRef(s);
}

bool isTuple(std::string s) {
    s = trim(s);
    if (isElem(s))
        return true;

    if (s[0] != Constants::CHAR_OPEN_TUPLE || s[s.length() - 1] != Constants::CHAR_CLOSE_TUPLE) {
        return false;
    }

    std::vector<std::string> elems = split(s.substr(1, s.length() - 2), ',');
    for (int i = 0; i < elems.size(); i++) {
        if (!isElem(elems[i]))
            return false;
    }
    return true;
}

bool isBoolean(std::string s) {
    return trim(s) == Constants::BOOLEAN_PATTERN;
}

bool isResultCl(string s) {
    return isTuple(s) || isBoolean(s);
}

ArgType findsStmtRefArgType(std::string ref) {
    if (isSynonym(ref)) {
        return ArgType::SYNONYM;
    }
    else if (isUnderscore(ref)) {
        return ArgType::WILDCARD;
    }
    else {
        return ArgType::CONSTANT;
    }
}

ArgType findsEntRefArgType(std::string ref) {
    if (isSynonym(ref)) {
        return ArgType::SYNONYM;
    }
    else if (isUnderscore(ref)) {
        return ArgType::WILDCARD;
    }
    else {
        return ArgType::EXPRESSION;
    }
}

ArgType findsExpressionSpecArgType(std::string ref) {
    if (isQuotedExpressionSpec(ref)) {
        return ArgType::EXPRESSION;
    }
    else if (isWildcardQuotedExpressionSpec(ref)) {
        return ArgType::WILDCARD_EXPR;
    }
    else {
        return ArgType::WILDCARD;
    }
}

ArgType findsRefArgType(std::string ref) {
    if (isQuotedIdent(ref)) {
        return ArgType::EXPRESSION;
    }
    else if (isInteger(ref)) {
        return ArgType::CONSTANT;
    }
    else {
        return ArgType::ATTRREF;
    }
}

Argument findsElemArg(std::string elem) {
    if (isSynonym(elem)) {
        return {ArgType::SYNONYM, elem};
    }
    else if (isAttrRef(elem)) {
        return {ArgType::ATTRREF, elem};
    }
}

bool isWith(std::string s) {
    return trim(s) == Constants::WITH_PATTERN;
}

bool isAttrCompare(std::string s) {
    s = trim(s);
    size_t equalInd = s.find(Constants::CHAR_EQUAL);
    if (equalInd == std::string::npos) {
        return false;
    }

    string leftRef = s.substr(0, equalInd);
    string rightRef = s.substr(equalInd + 1);
    return isRef(leftRef) && isRef(rightRef);
}

bool isQuotedIdent(std::string s) {
    s = trim(s);
    if (s.length() >= 2 &&
        ((s[0] == Constants::CHAR_DOUBLE_QUOTE && s[s.length() - 1] == Constants::CHAR_DOUBLE_QUOTE) ||
         (s[0] == Constants::CHAR_SINGLE_QUOTE && s[s.length() - 1] == Constants::CHAR_SINGLE_QUOTE))) {
        return isIdent(s.substr(1, s.length() - 2));
    }
    return false;
}

bool isRef(std::string s) {
    return isQuotedIdent(s) || isInteger(s) || isAttrRef(s);
}

void validatePatternType(EntityType patternType, std::string patternClause) {
    std::vector<std::string> patArg = split(patternClause.substr(1, patternClause.length() - 2), ',');
    std::string entRef = patArg[0];
    std::string exprSpec = patArg[1];

    if (patternType == EntityType::ASSIGN) {
        if (patArg.size() != 2 || !isEntRef(entRef) || !isExpressionSpec(exprSpec)) {
            throw SyntacticException("Invalid assign pattern clause");
        }
    }
    else if (patternType == EntityType::WHILE) {
        if (patArg.size() != 2 || !isEntRef(entRef) || !isUnderscore(exprSpec)) {
            throw SyntacticException("Invalid while pattern clause");
        }
    }
    else {
        if (patArg.size() != 3 || !isEntRef(entRef) || !isUnderscore(exprSpec) || !isUnderscore(patArg[2])) {
            throw SyntacticException("Invalid if pattern clause");
        }
    }
}

bool isAnd(std::string s) {
    return trim(s) == Constants::AND_PATTERN;
}

bool isNot(std::string s) {
    return trim(s) == Constants::NOT_PATTERN;
}

std::string removeSpaceInQuotedIdent(std::string entRef) {
    std::string parsedEntRef = "\"" + trim(entRef.substr(1, entRef.length() - 2)) + "\"";
    return parsedEntRef;
}

std::string obtainArgInBrackets(const std::vector<QpsToken>& tokens, size_t& currentIndex) {
    std::string bracketArg = "";

    while (currentIndex < tokens.size()) {
        if (tokens[currentIndex].getType() == QpsTokenType::EMPTY) {
            throw SyntacticException("Invalid relation entity: ");
        }
        else if (tokens[currentIndex].getType() == QpsTokenType::RIGHT_PARENTHESIS) {
            bracketArg += tokens[currentIndex++].getValue();
            break;
        }
        bracketArg += tokens[currentIndex++].getValue();
    }

    return bracketArg;
}

std::string getAttrCompare(const std::vector<QpsToken>& tokens, size_t& currentIndex) {
    size_t equalInd = currentIndex;
    std::string attrCompare;

    while (equalInd < tokens.size()) {
        if (tokens[equalInd].getType() == QpsTokenType::EQUALS) {
            break;
        }
        equalInd++;
    }

    if (equalInd == tokens.size() - 1) {
        throw SyntacticException("Missing '=' in AttrCompare: ");
    }

    // Add up to equal sign
    while (currentIndex != equalInd) {
        attrCompare += tokens[currentIndex++].getValue();
    }
    attrCompare += tokens[currentIndex].getValue();
    currentIndex += 1;

    // Add the second arg
    attrCompare += parseSynOrAttrRef(tokens, currentIndex);

    if (!isAttrCompare(attrCompare)) {
        throw SyntacticException("Invalid AttrCompare: ");
    }

    return attrCompare;
}

std::string parseSynOrAttrRef(const std::vector<QpsToken>& tokens, size_t& currentIndex) {
    std::string finalStr;
    if (currentIndex + 1 < tokens.size() && tokens[currentIndex + 1].getType() == QpsTokenType::DOT) {
        finalStr += tokens[currentIndex].getValue() + tokens[currentIndex + 1].getValue();
        currentIndex += 2;
        if (currentIndex + 1 < tokens.size() && tokens[currentIndex + 1].getType() == QpsTokenType::HASH) {
            finalStr += tokens[currentIndex].getValue() + tokens[currentIndex + 1].getValue();
            currentIndex += 2;
        }
        else {
            finalStr += tokens[currentIndex++].getValue();
        }
    }
    else if (currentIndex < tokens.size()) {
        finalStr += tokens[currentIndex++].getValue();
    }
    else {
        throw SyntacticException("Missing Argument: ");
    }

    return finalStr;
}