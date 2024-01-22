#pragma once
#include "SP/AST/BinaryExpressionNode.h"
#include "SP/AST/ProgramNode.h"

const int MOCK_STMT_NUM = 12345;

namespace MockAssignments {
    // x = 1 + 2
    std::shared_ptr<AssignNode> mock0();
}

namespace MockWhile {
    // while (x < 0) { read x; }
    std::shared_ptr<WhileThenNode> mock0();
}

namespace MockIf {
    // if (y < 0) then { print y; } else { print x; }
    std::shared_ptr<IfThenElseNode> mock0();
}
