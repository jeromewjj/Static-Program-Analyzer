

#include "Validator.h"

void Validator::validateQuery(Query& query) {
    Rulebook::testDeclaration(query.declarations);

    Rulebook rulebook{query.declarations};

    rulebook.testSelClause(query.selClause);

    for (const auto& clause : query.clauses) {
        clause->visit(rulebook);
    }
}
