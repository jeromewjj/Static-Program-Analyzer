
#include "Rulebook.h"

void Rulebook::testDeclaration(const std::vector<Declaration>& declarations) {
    Rule::synonymDeclaredOnce(declarations);
}

Rulebook::Rulebook(const std::vector<Declaration>& declarations) {
    for (const auto& declaration : declarations) {
        map[declaration.synonym] = declaration.entityType;
    }
}

void Rulebook::testSelClause(const SelClause& clause) {
    if (clause.argument->type == ArgType::BOOLEAN) {
        return;
    }

    Rule::synonymUsedDeclared(map, clause.argument->getSynonyms());

    for (const auto& attrRef : clause.argument->getAttrRefs()) {
        Rule::validAttrRef(map, attrRef);
    }
}

void Rulebook::testSTClause(const Abstraction& abstraction) {
    std::vector<std::string> strings;
    for (const auto& arg : abstraction.args) {
        if (arg.type == ArgType::SYNONYM) {
            strings.push_back(arg.str);
        }
    }
    Rule::synonymUsedDeclared(map, strings);

    if (abstraction.type == AbstractionType::MODIFIES || abstraction.type == AbstractionType::USES) {
        Rule::firstArgNoWildcard(abstraction.args);
    }

    Rule::abstractionArgSynonymType(map, abstraction);
}

void Rulebook::testPatClause(const std::vector<Argument>& arguments) {
    std::vector<std::string> strings;
    for (const auto& arg : arguments) {
        if (arg.type == ArgType::SYNONYM) {
            strings.push_back(arg.str);
        }
    }
    Rule::synonymUsedDeclared(map, strings);

    const auto patternType = Rule::patternEntityRule(map, arguments[0]);

    Rule::patternArgSynonymType(map, patternType, {arguments[1]});
}

Attribute::ValType Rulebook::checkWithArg(const Argument& argument) {
    if (argument.type == ArgType::CONSTANT) {
        return Attribute::ValType::INT;
    }
    if (argument.type == ArgType::EXPRESSION) {
        return Attribute::ValType::STRING;
    }
    return Rule::validAttrRef(map, argument.str);
}

void Rulebook::testWithClause(const AttrCompare& attrCompare) {
    auto type1 = Rulebook::checkWithArg(attrCompare.leftArg);
    auto type2 = Rulebook::checkWithArg(attrCompare.rightArg);

    Rule::validAttrCompare(type1, type2);
}
