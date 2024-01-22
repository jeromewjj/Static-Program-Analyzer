#include <utility>

#import "AbstractionRules.h"
#import "PatternRules.h"
#import "QPS/Declaration/Declaration.h"
#import "QPS/Evaluator/Entity/Attribute.h"
#import "QPS/QPSException/SemanticException.h"

#pragma once

namespace Rule {

    using DeclarationMap = std::unordered_map<std::string, EntityType>;

    void synonymDeclaredOnce(const std::vector<Declaration>& declarations);

    void synonymUsedDeclared(DeclarationMap& map, const std::vector<std::string>& synonyms);

    EntityType patternEntityRule(DeclarationMap& map, const Argument& patternSynonym);

    void firstArgNoWildcard(const std::vector<Argument>& arguments);

    void abstractionArgSynonymType(DeclarationMap& map, const Abstraction& abstraction);

    void patternArgSynonymType(DeclarationMap& map, EntityType type, const std::vector<Argument>& arguments);

    Attribute::ValType validAttrRef(DeclarationMap& map, const std::string& argStr);

    void validAttrCompare(Attribute::ValType type1, Attribute::ValType type2);
}
