#pragma once
#include "SP/AST/ASTNode.h"
#include "SP/SemanticValidator/ValidationRules/Validation.h"
#include "SemanticValidatorManager.h"

class SemanticValidator {
public:
    void validate(const ASTNodePtr_VIEWONLY& rootNode);
    template <typename ValidationRule> void addRule(SemanticValidatorManager& manager);
};
