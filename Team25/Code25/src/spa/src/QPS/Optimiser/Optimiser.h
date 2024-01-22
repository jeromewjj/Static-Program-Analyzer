#pragma once

#include <algorithm>
#include <vector>

#include "QPS/Clause/CondClause.h"

class Optimiser {
public:
    static void Optimise(std::vector<CondClause*>& clauses);
    static void sortCondClausesBySynonymLength(std::vector<CondClause*>& clauses);

private:
    static bool compareCondClausesBySynonymLength(CondClause* clause1, CondClause* clause2);
};
