#include "SemanticValidator.h"

#include "SP/SemanticValidator/ValidationRules/CallSemantics.h"
#include "SP/SemanticValidator/ValidationRules/NoDuplicateProcedures.h"
#include "SP/SemanticValidator/ValidationRules/Validation.h"

void SemanticValidator::validate(const ASTNodePtr_VIEWONLY& rootNode) {
    SemanticValidatorManager manager{};

    addRule<CallSemantics>(manager);
    addRule<NoDuplicateProcedures>(manager);

    manager.validateAll(rootNode);
}

template <typename ValidationRule> void SemanticValidator::addRule(SemanticValidatorManager& manager) {
    auto validationRule = std::make_shared<ValidationRule>();
    manager.addValidationRule(validationRule);
}