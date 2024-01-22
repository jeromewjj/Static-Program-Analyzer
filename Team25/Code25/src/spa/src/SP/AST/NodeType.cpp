#include "NodeType.h"

#include <string>

std::string nodeTypeToString(NodeType type) {
    std::map<NodeType, std::string> nodeTypeToString = {
        {NodeType::PROGRAM, "Program"},
        {NodeType::PROCEDURE, "Procedure"},
        {NodeType::STMT_LIST, "StmtList"},

        // statements
        {NodeType::WHILE_THEN, "WhileThen"},
        {NodeType::IF_THEN_ELSE, "IfThenElse"},
        {NodeType::READ, "Read"},
        {NodeType::PRINT, "Print"},
        {NodeType::ASSIGN, "Assign"},
        {NodeType::CALL, "Call"},

        {NodeType::VARIABLE, "Variable"},
        {NodeType::CONSTANT, "Constant"},

        {NodeType::BINARY_EXPRESSION, "BinaryExpression"},
        {NodeType::UNARY_EXPRESSION, "UnaryExpression"},
    };

    auto itr = nodeTypeToString.find(type);
    if (itr != nodeTypeToString.end()) {
        return itr->second;
    }
    return "UNKNOWN_NODE_TYPE";
}

bool isStmtNode(NodeType nodeType) {
    std::unordered_set<NodeType> stmtNodeTypes{
        NodeType::READ, NodeType::PRINT, NodeType::ASSIGN, NodeType::CALL, NodeType::WHILE_THEN, NodeType::IF_THEN_ELSE,
    };
    if (stmtNodeTypes.find(nodeType) == stmtNodeTypes.end()) {
        return false;
    }
    return true;
}