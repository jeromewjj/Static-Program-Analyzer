#include "UsesStrategy.h"

// UsesS : 'Uses' '(' stmtRef ',' entRef ')'
// UsesP: 'Uses' '(' entRef ',' entRef ')'
std::vector<Argument> UsesStrategy::parseArgs(std::string ref1, std::string ref2) {
    if (isStmtRef(ref1) && isEntRef(ref2)) {
        Argument stmtRefArg = Argument(findsStmtRefArgType(ref1), ref1);
        Argument entRefArg = Argument(findsEntRefArgType(ref2), ref2);
        std::vector<Argument> argList{stmtRefArg, entRefArg};
        return argList;
    }
    else if (isEntRef(ref1) && isEntRef(ref2)) {
        Argument entRefArg1 = Argument(findsEntRefArgType(ref1), ref1);
        Argument entRefArg2 = Argument(findsEntRefArgType(ref2), ref2);
        std::vector<Argument> argList{entRefArg1, entRefArg2};
        return argList;
    }
    throw std::runtime_error("Invalid Ref for Uses: ");
}