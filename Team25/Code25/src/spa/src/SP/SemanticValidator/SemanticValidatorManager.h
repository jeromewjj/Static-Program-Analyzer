#pragma once
#include "SP/SemanticValidator/ValidationRules/Validation.h"

class SemanticValidatorManager {
public:
    void validateAll(const ASTNodePtr_VIEWONLY& rootNode) {
        for (const auto& x : validationRules) {
            x->validate(rootNode);
        }
    }

    void addValidationRule(const std::shared_ptr<Validation>& x) {
        validationRules.insert(x);
    }

private:
    std::unordered_set<std::shared_ptr<Validation>> validationRules;
};