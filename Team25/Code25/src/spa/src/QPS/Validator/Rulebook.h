#include "QPS/Clause/SelClause.h"
#include "QPS/Clause/WithClause/AttrCompare.h"
#import "Rules/Rule.h"

#ifndef SPA_RULEBOOK_H
#define SPA_RULEBOOK_H

class Rulebook {
    using DeclarationMap = std::unordered_map<std::string, EntityType>;

    DeclarationMap map;
    Attribute::ValType checkWithArg(const Argument& argument);

public:
    explicit Rulebook(const std::vector<Declaration>& declarations);
    static void testDeclaration(const std::vector<Declaration>& declarations);
    void testSelClause(const SelClause& clause);
    void testSTClause(const Abstraction& abstraction);
    void testPatClause(const std::vector<Argument>& arguments);
    void testWithClause(const AttrCompare& attrCompare);
};

#endif // SPA_RULEBOOK_H
