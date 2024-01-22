#pragma once

#include <map>
#include <string>
#include <unordered_set>

enum class NodeType {
    PROGRAM,
    PROCEDURE,
    STMT_LIST,

    // inherits StatementNode
    READ,
    PRINT,
    ASSIGN,
    CALL,
    WHILE_THEN,
    IF_THEN_ELSE,

    // expressions (eg. math_expr & conditional_expr)
    BINARY_EXPRESSION,
    UNARY_EXPRESSION,

    // terms
    VARIABLE,
    CONSTANT
};

std::string nodeTypeToString(NodeType type);

// mainly for assertion within StmtList Node
// not very necessary because
// all statementsNodes inherits StatementNode so can check that type
bool isStmtNode(NodeType nodeType);
