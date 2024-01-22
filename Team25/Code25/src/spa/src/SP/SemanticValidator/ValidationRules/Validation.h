#pragma once
#include "SP/AST/ASTNode.h"

class Validation {
public:
    virtual void validate(ASTNodePtr_VIEWONLY rootNode) const = 0;
};