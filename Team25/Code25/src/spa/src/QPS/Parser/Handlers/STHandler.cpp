#include "STHandler.h"

std::unique_ptr<CondClause> STHandler::handle(std::vector<QpsToken>& tokens, size_t& currentIndex) {
    if (currentIndex + 1 >= tokens.size()) {
        return nullptr;
    }

    // If this is an and followed after a such that clause
    // Will skip checking of 'such that' keyword
    if (!isAnd) {
        string potentialSuch = tokens[currentIndex].getValue();
        if (!isSuch(potentialSuch)) {
            return nullptr;
        }
        string potentialThat = tokens[currentIndex + 1].getValue();
        if (!isThat(potentialThat)) {
            throw SyntacticException("Invalid such that clause: ");
        }
        currentIndex += 2;
    }

    bool isNegate = false;
    if (isNot(tokens[currentIndex].getValue())) {
        isNegate = true;
        currentIndex++;
    }

    RelationStrategyManager manager;
    std::string relRef = obtainArgInBrackets(tokens, currentIndex);

    if (!isRelRef(relRef)) {
        throw SyntacticException("Invalid relation reference: ");
    }

    auto [rel, ref1, ref2] = parseRef(relRef);

    if (query.find(rel) == std::string::npos) {
        throw SyntacticException("Invalid relation format: ");
    }

    Abstraction abstraction = manager.parseAbstraction(rel, ref1, ref2);
    STClause stClause(abstraction, isNegate);
    return std::make_unique<STClause>(stClause);
}