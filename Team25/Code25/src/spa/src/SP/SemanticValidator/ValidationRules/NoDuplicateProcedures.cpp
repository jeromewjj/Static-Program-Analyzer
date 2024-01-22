#include "NoDuplicateProcedures.h"

#include <memory>

#include "SP/AST/ProgramNode.h"
#include "SP/Parser/ParserException.h"

void NoDuplicateProcedures::validate(ASTNodePtr_VIEWONLY rootNode) const {
    std::shared_ptr<const ProgramNode> programNode = std::static_pointer_cast<const ProgramNode>(rootNode);

    std::unordered_set<string> procNames{};
    for (const auto& procNode : programNode->getProcedures()) {
        const string name = procNode->getName();
        if (procNames.find(name) != procNames.end()) {
            throw ParserException("No Duplicate Procedure Names allowed");
        }
        procNames.insert(name);
    }
}
