#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "Constants.h"
#include "Parser/ParserUtil.h"
#include "QPS/Argument/Argument.h"
#include "QPS/Evaluator/Entity/Entity.h"
#include "QPS/QPSException/SyntacticException.h"
#include "QPS/Tokenizer/QpsToken.h"

bool isName(std::string s);

bool isIdent(std::string s);

bool isInteger(std::string s);

bool isSynonym(std::string s);

bool isDesignEntity(std::string s);

bool isDeclaration(std::string designEntityToken, std::string synonymToken, std::string semiColonToken);

bool isMultiDeclaration(std::string designEntityToken, std::string synonymToken, std::string commaToken);

bool isSelect(std::string s);

bool isSuch(std::string s);

bool isThat(std::string s);

bool isStmtRef(std::string s);

bool isEntRef(std::string s);

bool isFollows(std::string s);

bool isFollowsT(std::string s);

bool isParent(std::string s);

bool isParentT(std::string s);

bool isUsesS(std::string s);

bool isUsesP(std::string s);

bool isModifiesS(std::string s);

bool isModifiesP(std::string s);

bool isCalls(std::string s);

bool isCallsT(std::string s);

bool isNext(std::string s);

bool isNextT(std::string s);

bool isAffects(std::string s);

bool isRelRef(std::string s);

std::tuple<std::string, std::string, std::string> parseRef(std::string s);

bool isFactor(std::string s);

bool isVarName(std::string s);

bool isVarName(std::string s);

bool isConstValue(std::string s);

bool isTerm(std::string s);

bool isExpr(std::string s);

bool isExpressionSpec(std::string s);

bool isWildcardQuotedExpressionSpec(std::string s);

bool isQuotedExpressionSpec(std::string s);

bool isPattern(std::string s);

bool isUnderscore(std::string s);

bool isAttrName(std::string s);

bool isAttrRef(std::string s);

bool isElem(std::string s);

bool isTuple(std::string s);

bool isBoolean(std::string s);

bool isResultCl(string s);

ArgType findsStmtRefArgType(std::string ref);

ArgType findsEntRefArgType(std::string ref);

ArgType findsExpressionSpecArgType(std::string ref);

ArgType findsRefArgType(std::string ref);

Argument findsElemArg(std::string elem);

bool isWith(std::string s);

bool isAttrCompare(std::string s);

bool isQuotedIdent(std::string s);

bool isRef(std::string s);

void validatePatternType(EntityType patternType, std::string patternClause);

bool isAnd(std::string s);

bool isNot(std::string s);

std::string removeSpaceInQuotedIdent(std::string entRef);

std::string obtainArgInBrackets(const std::vector<QpsToken>& tokens, size_t& currentIndex);

std::string getAttrCompare(const std::vector<QpsToken>& tokens, size_t& currentIndex);

std::string parseSynOrAttrRef(const std::vector<QpsToken>& tokens, size_t& currentIndex);