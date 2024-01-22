#include "PatHandler.h"

const std::unordered_set<EntityType> POSSIBLE_PAT_TYPES = {EntityType::ASSIGN, EntityType::WHILE, EntityType::IF};

std::unique_ptr<CondClause> PatHandler::handle(std::vector<QpsToken>& tokens, size_t& currentIndex) {
    if (currentIndex >= tokens.size()) {
        return nullptr;
    }

    // If this is an and followed after a pattern clause
    // Will skip checking of 'pattern' keyword
    if (!isAnd) {
        std::string potentialPattern = tokens[currentIndex].getValue();
        if (!isPattern(potentialPattern)) {
            return nullptr;
        }

        currentIndex++;
    }

    bool isNegate = false;
    if (isNot(tokens[currentIndex].getValue())) {
        isNegate = true;
        currentIndex++;
    }

    // Pattern clause should contain at least 5 tokens
    if (currentIndex + 5 >= tokens.size()) {
        throw SyntacticException("Invalid pattern clause: ");
    }

    // Validate synPat is assign, while or if synonym
    std::string synPat = tokens[currentIndex++].getValue();
    EntityType synPatEntityType;
    synPatEntityType = assignSynEntityType(declarations, synPat);

    std::string patternClause;
    size_t endPatInd = currentIndex;

    patternClause = obtainArgInBrackets(tokens, endPatInd);

    size_t startParenInd = patternClause.find('(');
    size_t endParenInd = patternClause.find(')');

    if (startParenInd == std::string::npos || endParenInd == std::string::npos) {
        throw SyntacticException("Invalid pattern clause: ");
    }

    std::vector<std::string> patArg = split(patternClause.substr(1, patternClause.length() - 2), ',');
    std::string entRef = patArg[0];
    std::string exprSpec = patArg[1];

    validatePatternType(synPatEntityType, patternClause);

    if (isQuotedIdent(entRef)) {
        entRef = removeSpaceInQuotedIdent(entRef);
    }

    currentIndex = endPatInd;
    exprSpec = parseExprInExprSpec(exprSpec);

    PatClause patClause(synPat, entRef, exprSpec, synPatEntityType, isNegate);
    return std::make_unique<PatClause>(patClause);
}

EntityType PatHandler::assignSynEntityType(std::vector<Declaration>& declarations, std::string synPat) {
    for (const auto& declaration : declarations) {
        if (declaration.synonym == synPat) {
            if (!POSSIBLE_PAT_TYPES.count(declaration.entityType)) {
                throw SemanticException(ErrorMessage::INVALID_SYNONYM_PAT(declaration.synonym));
            }
            return declaration.entityType;
        }
    }

    // Implies no declaration of the Pattern synonym
    throw SemanticException(ErrorMessage::INVALID_SYNONYM(synPat));
}

std::string PatHandler::parseExprInExprSpec(std::string exprSpec) {
    if (exprSpec != Constants::UNDERSCORE) {
        exprSpec = trim(exprSpec);
        std::string exprOnly;
        if (isWildcardQuotedExpressionSpec(exprSpec)) {
            exprOnly = exprSpec.substr(2, exprSpec.length() - 4);
            std::shared_ptr<std::string> parsedExpr = parseExpression(exprOnly);
            exprSpec = "_\"" + *parsedExpr + "\"_";
        }
        else {
            exprOnly = exprSpec.substr(1, exprSpec.length() - 2);
            std::shared_ptr<std::string> parsedExpr = parseExpression(exprOnly);
            exprSpec = "\"" + *parsedExpr + "\"";
        }
    }
    return exprSpec;
}