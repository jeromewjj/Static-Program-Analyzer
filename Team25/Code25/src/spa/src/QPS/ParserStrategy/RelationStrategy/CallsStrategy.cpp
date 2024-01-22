#include "CallsStrategy.h"

// Calls : 'Calls' '(' entRef ',' entRef ')'
// CallsT : 'Calls*' '(' entRef ',' entRef ')'
std::vector<Argument> CallsStrategy::parseArgs(std::string ref1, std::string ref2) {
    if (isEntRef(ref1) && isEntRef(ref2)) {
        Argument entRefArg1 = Argument(findsEntRefArgType(ref1), ref1);
        Argument entRefArg2 = Argument(findsEntRefArgType(ref2), ref2);
        std::vector<Argument> argList{entRefArg1, entRefArg2};
        return argList;
    }
    throw std::runtime_error("Invalid entRef for Calls: ");
}