#include "FollowsStrategy.h"

// Follows : 'Follows' '(' stmtRef ',' stmtRef ')'
// FollowsT : 'Follows*' '(' stmtRef ',' stmtRef ')'
std::vector<Argument> FollowsStrategy::parseArgs(std::string ref1, std::string ref2) {
    if (isStmtRef(ref1) && isStmtRef(ref2)) {
        Argument stmtRefArg1 = Argument(findsStmtRefArgType(ref1), ref1);
        Argument stmtRefArg2 = Argument(findsStmtRefArgType(ref2), ref2);
        std::vector<Argument> argList{stmtRefArg1, stmtRefArg2};
        return argList;
    }
    throw std::runtime_error("Invalid stmtRef for Follows: ");
}