#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include <string>
#include <vector>

#include "QPS/Clause/CondClause.h"
#include "QPS/Clause/SelClause.h"
#include "QPS/Declaration/Declaration.h"

struct Query {
    SelClause selClause;
    const std::vector<Declaration> declarations;
    const std::vector<CondClause*> clauses;
};

#endif // SPA_QUERY_H