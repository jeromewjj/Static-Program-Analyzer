#pragma once
#include "SP/AST/ProgramNode.h"
#include "Validation.h"

class CallSemantics : public Validation {
public:
    void validate(ASTNodePtr_VIEWONLY rootNode) const override;

    static std::unordered_map<string, unordered_set<string>>
    getProceduresCallingProcedure(const std::shared_ptr<const ProgramNode>& programNode);
};
