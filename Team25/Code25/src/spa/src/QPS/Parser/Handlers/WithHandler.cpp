//
// Created by User on 2/11/2023.
//

#include "WithHandler.h"

std::unique_ptr<CondClause> WithHandler::handle(std::vector<QpsToken>& tokens, size_t& currentIndex) {
    // If this is an and followed after a with clause
    // Will skip checking of 'with' keyword
    if (!isAnd) {
        if (currentIndex >= tokens.size() || !isWith(tokens[currentIndex].getValue())) {
            return nullptr;
        }
        currentIndex++;
    }

    std::string attrCond;

    // First attrCompare contains a NOT
    if (tokens[currentIndex].getType() == QpsTokenType::NOT) {
        attrCond += Constants::NOT_PATTERN + Constants::SPACE;
        currentIndex++;
    }

    if (currentIndex + 2 >= tokens.size()) {
        throw SyntacticException("Invalid With clause: ");
    }

    // Obtain attrCompare in the format ref=ref
    attrCond += getAttrCompare(tokens, currentIndex);

    return std::make_unique<WithClause>(WithClause(attrCond));
}
