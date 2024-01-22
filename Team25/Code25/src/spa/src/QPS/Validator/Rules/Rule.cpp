//
// Created by Edward Alvin on 25/10/23.
//

#include "Rule.h"

#include "QPS/Evaluator/Util.h"

namespace Rule {
    void synonymDeclaredOnce(const std::vector<Declaration>& declarations) {
        std::unordered_set<std::string> declaredSynonyms;
        for (const auto& declaration : declarations) {
            if (declaredSynonyms.count(declaration.synonym) == 1) {
                throw SemanticException();
            }
            declaredSynonyms.insert(declaration.synonym);
        }
    }

    void synonymUsedDeclared(DeclarationMap& map, const std::vector<std::string>& synonyms) {
        for (const auto& synonym : synonyms) {
            if (map.count(synonym) != 1) {
                throw SemanticException();
            }
        }
    }

    EntityType patternEntityRule(DeclarationMap& map, const Argument& patternSynonym) {
        if (patternSynonym.type == ArgType::SYNONYM && map.count(patternSynonym.str) == 1) {
            return map.at(patternSynonym.str);
        }
        throw SemanticException();
    }

    void firstArgNoWildcard(const std::vector<Argument>& arguments) {
        if (arguments.empty() || arguments[0].type == ArgType::WILDCARD) {
            throw SemanticException();
        }
    }

    void abstractionArgSynonymType(DeclarationMap& map, const Abstraction& abstraction) {
        const auto& rules = AbstractionRules::RULES.at(abstraction.type);
        if (rules.size() != abstraction.args.size()) {
            throw SemanticException();
        }

        for (size_t i = 0; i < rules.size(); i++) {
            if (abstraction.args[i].type != ArgType::SYNONYM) {
                continue;
            }
            const auto& type = map.at(abstraction.args[i].str);
            if (rules[i].count(type) != 1) {
                throw SemanticException();
            }
        }
    }

    void patternArgSynonymType(DeclarationMap& map, EntityType entityType, const std::vector<Argument>& arguments) {
        const auto& rules = PatternRules::RULES.at(entityType);
        if (rules.size() != arguments.size()) {
            throw SemanticException();
        }

        for (size_t i = 0; i < rules.size(); i++) {
            if (arguments[i].type != ArgType::SYNONYM) {
                continue;
            }
            const auto& type = map.at(arguments[i].str);
            if (rules[i].count(type) != 1) {
                throw SemanticException();
            }
        }
    }

    Attribute::ValType validAttrRef(DeclarationMap& map, const std::string& argStr) {
        auto vec = EvalUtil::split(argStr, EvalUtil::DOT);
        auto synonym = vec[0];
        auto rawAttr = vec[1];

        auto type = map.at(synonym);
        auto attr = Attribute::RAW_TO_ATTR.at(rawAttr);

        if (Attribute::ENT_TO_ATTR.at(type).count(attr) == 0) {
            throw SemanticException();
        }

        return Attribute::ATTR_TO_VAL.at(attr);
    }

    void validAttrCompare(Attribute::ValType type1, Attribute::ValType type2) {
        if (type1 != type2) {
            throw SemanticException();
        }
    }
}