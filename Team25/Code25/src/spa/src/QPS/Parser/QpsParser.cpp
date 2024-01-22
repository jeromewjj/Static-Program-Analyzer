#include "QPS/Parser/QpsParser.h"

const std::unordered_set<EntityType> POSSIBLE_PAT_TYPES = {EntityType::ASSIGN, EntityType::WHILE, EntityType::IF};

QpsParser::QpsParser() : tokenizer(std::unique_ptr<QpsTokenizer>()) {
    validEntities = {{"stmt", EntityType::STATEMENT},    {"read", EntityType::READ},
                     {"print", EntityType::PRINT},       {"call", EntityType::CALL},
                     {"while", EntityType::WHILE},       {"if", EntityType::IF},
                     {"assign", EntityType::ASSIGN},     {"variable", EntityType::VARIABLE},
                     {"constant", EntityType::CONSTANT}, {"procedure", EntityType::PROCEDURE}};
}

Query QpsParser::parseQuery(std::string& query) {
    std::vector<Declaration> declarations;
    std::unique_ptr<SelClause> selClause;
    std::vector<CondClause*> clauses;
    std::vector<QpsToken> tokens = tokenizer->tokenize(query);
    std::string prevParsedClause;
    bool isAnd = false;

    for (size_t i = 0; i < tokens.size();) {
        // Encounter a potential Declaration
        handlePotentialDeclaration(tokens, i, declarations);

        // Encounter a potential Select
        if (!selClause) {
            selClause = handlePotentialSelect(tokens, i, declarations);
            if (selClause)
                continue;
        }

        // Encounter a potential Such that clause
        STHandler stHandler(tokens, i, isAnd, query);
        std::unique_ptr<CondClause> stClause = stHandler.handle(tokens, i);
        if (stClause) {
            clauses.push_back(stClause.release());
            prevParsedClause = Constants::SUCH_PATTERN;
            continue;
        }

        // Encounter a potential Pattern clause
        PatHandler patHandler(tokens, i, declarations, isAnd);
        std::unique_ptr<CondClause> patClause = patHandler.handle(tokens, i);
        if (patClause) {
            clauses.push_back(patClause.release());
            prevParsedClause = Constants::PATTERN_PATTERN;
            continue;
        }

        // Encounter a potential With clause
        WithHandler withHandler(tokens, i, isAnd);
        std::unique_ptr<CondClause> withClause = withHandler.handle(tokens, i);
        if (withClause) {
            clauses.push_back(withClause.release());
            prevParsedClause = Constants::WITH_PATTERN;
            continue;
        }

        // Encounter a potential And
        AndHandler andHandler(tokens, i, prevParsedClause, declarations, query);
        std::unique_ptr<CondClause> andClause = andHandler.handle(tokens, i);
        if (andClause) {
            clauses.push_back(andClause.release());
            continue;
        }

        i++;
    }

    if (selClause == nullptr) {
        throw SyntacticException("Invalid query format: ");
    }

    return {*selClause, declarations, clauses};
}

void QpsParser::handlePotentialDeclaration(const std::vector<QpsToken>& tokens, size_t& currentIndex,
                                           std::vector<Declaration>& declarations) {
    if (currentIndex + 2 >= tokens.size())
        return;

    std::string designEntity = tokens[currentIndex].getValue();
    std::string punctuation = tokens[currentIndex + 2].getValue();
    std::string synonym = tokens[currentIndex + 1].getValue();

    if (!isDesignEntity(designEntity) && (punctuation == Constants::SEMICOLON || punctuation == Constants::COMMA))
        throw SyntacticException("Invalid declaration design entity: ");

    if (!isDesignEntity(designEntity))
        return;

    if (punctuation != Constants::SEMICOLON && punctuation != Constants::COMMA)
        throw SyntacticException("Invalid declaration format: ");

    EntityType entityType = validEntities[designEntity];
    Declaration declaration = {entityType, synonym};

    if (!isDeclaration(designEntity, synonym, punctuation) && !isMultiDeclaration(designEntity, synonym, punctuation)) {
        throw SyntacticException("Invalid declaration synonym: ");
    }

    currentIndex += 2;
    declarations.push_back(declaration);

    if (isMultiDeclaration(designEntity, synonym, punctuation)) {
        bool endOfDeclarations = false;
        while (currentIndex + 2 < tokens.size()) {
            synonym = tokens[currentIndex + 1].getValue();
            punctuation = tokens[currentIndex + 2].getValue();

            if (punctuation != Constants::SEMICOLON && punctuation != Constants::COMMA)
                throw SyntacticException("Invalid declaration format: " + punctuation);

            Declaration declaration = {entityType, synonym};
            declarations.push_back(declaration);
            currentIndex += 2;

            if (punctuation == Constants::SEMICOLON) {
                endOfDeclarations = true;
                break;
            }
        }

        if (!endOfDeclarations) {
            throw SyntacticException("Invalid multi declaration format: ");
        }
    }
}

bool QpsParser::isExistingDeclaration(const std::string& syn, std::vector<Declaration>& declarations) {
    for (auto declaration : declarations) {
        if (declaration.synonym == syn)
            return true;
    }
    return false;
}

std::unique_ptr<SelClause> QpsParser::handlePotentialSelect(const std::vector<QpsToken>& tokens, size_t& currentIndex,
                                                            std::vector<Declaration>& declarations) {
    if (currentIndex < tokens.size() && isSelect(tokens[currentIndex].getValue())) {
        if (currentIndex + 1 >= tokens.size()) {
            throw SyntacticException("Missing resultCl for Select clause: ");
        }

        // Potentially a BOOLEAN
        std::string booleanStr = tokens[currentIndex + 1].getValue();
        if (isBoolean(booleanStr)) {
            if (!isExistingDeclaration(booleanStr, declarations)) {
                currentIndex += 2;
                auto boolArg = std::make_shared<Argument>(ArgType::BOOLEAN, booleanStr);
                return std::make_unique<SelClause>(SelClause(boolArg));
            }
        }

        // Potentially an elem or tuple
        auto tupleArg = generateTuple(tokens, currentIndex);
        return std::make_unique<SelClause>(SelClause(tupleArg));
    }
    return nullptr;
}

std::shared_ptr<Tuple> QpsParser::generateTuple(const std::vector<QpsToken>& tokens, size_t& currentIndex) {
    std::vector<Argument> listOfTupleArgs;
    std::string tupleStr;

    // Potentially multiple elems
    if (tokens[currentIndex + 1].getType() == QpsTokenType::TUPLE_OPEN_BRACKET) {
        currentIndex++;
        while (currentIndex < tokens.size()) {
            if (tokens[currentIndex].getType() == QpsTokenType::EMPTY) {
                throw SyntacticException("Invalid tuple: ");
            }
            else if (tokens[currentIndex].getType() == QpsTokenType::TUPLE_CLOSE_BRACKET) {
                tupleStr += tokens[currentIndex++].getValue();
                break;
            }
            tupleStr += tokens[currentIndex++].getValue();
        }

        std::vector<std::string> listOfTupleElems = split(tupleStr.substr(1, tupleStr.length() - 2), ',');
        for (auto& elem : listOfTupleElems) {
            if (!isElem(elem)) {
                throw SyntacticException("Invalid elem in tuple: ");
            }
            listOfTupleArgs.push_back(findsElemArg(elem));
        }
    }
    else { // Potentially an elem
        currentIndex++;
        std::string elem = parseSynOrAttrRef(tokens, currentIndex);
        if (!isElem(elem)) {
            throw SyntacticException("Invalid elem in tuple: ");
        }
        tupleStr += elem;
        listOfTupleArgs.push_back(findsElemArg(elem));
    }
    return std::make_shared<Tuple>(Tuple(listOfTupleArgs, tupleStr));
}
