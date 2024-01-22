#include "WithClause.h"

WithClause::WithClause(std::string attrCond) {
    size_t equalPos = attrCond.find(Constants::CHAR_EQUAL);
    if (equalPos == std::string::npos) {
        throw SyntacticException("Invalid attrcond in with clause: ");
    }

    bool isNot = false;
    size_t notPos = attrCond.find(Constants::NOT_PATTERN);
    if (notPos != std::string::npos) {
        isNot = true;
    }
    this->isNot = isNot;

    std::string leftArgStr;
    std::string rightArgStr;
    attrCond = trim(attrCond);

    if (isNot) {
        leftArgStr = attrCond.substr(notPos + 4, equalPos - 4); // Start substr after 'not '
        rightArgStr = attrCond.substr(equalPos + 1);
    }
    else {
        leftArgStr = attrCond.substr(0, equalPos);
        rightArgStr = attrCond.substr(equalPos + 1);
    }

    if (!isRef(leftArgStr) || !isRef(rightArgStr)) {
        throw SyntacticException("Invalid ref in with clause: ");
    }

    Argument leftArg(findsRefArgType(leftArgStr), leftArgStr);
    Argument rightArg(findsRefArgType(rightArgStr), rightArgStr);

    attrCompare = std::make_unique<AttrCompare>(AttrCompare(leftArg, rightArg));
}

void WithClause::visit(Rulebook& rulebook) {
    rulebook.testWithClause(*attrCompare);
}

std::vector<std::string> WithClause::getSynonyms() {
    std::vector<std::string> res;
    if (!attrCompare->leftArg.getSynonyms().empty()) {
        res.push_back(attrCompare->leftArg.getSynonyms()[0]);
    }
    if (!attrCompare->rightArg.getSynonyms().empty()) {
        res.push_back(attrCompare->rightArg.getSynonyms()[0]);
    }
    return res;
}

std::shared_ptr<ClauseStrategy> WithClause::getStrat() {
    return std::make_shared<WithStrategy>(attrCompare->leftArg, attrCompare->rightArg);
}
