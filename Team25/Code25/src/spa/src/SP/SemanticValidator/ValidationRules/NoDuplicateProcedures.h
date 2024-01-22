#pragma once
#include "Validation.h"

class NoDuplicateProcedures : public Validation {
public:
    void validate(ASTNodePtr_VIEWONLY rootNode) const override;
};
