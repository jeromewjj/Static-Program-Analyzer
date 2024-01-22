#include "Optimiser.h"

void Optimiser::Optimise(std::vector<CondClause*>& clauses) {
    Optimiser::sortCondClausesBySynonymLength(clauses);
}

bool Optimiser::compareCondClausesBySynonymLength(CondClause* clause1, CondClause* clause2) {
    const std::vector<std::string> synonyms1 = clause1->getSynonyms();
    const std::vector<std::string> synonyms2 = clause2->getSynonyms();

    return synonyms1.size() < synonyms2.size();
}

void Optimiser::sortCondClausesBySynonymLength(std::vector<CondClause*>& clauses) {
    std::sort(clauses.begin(), clauses.end(), compareCondClausesBySynonymLength);
}
