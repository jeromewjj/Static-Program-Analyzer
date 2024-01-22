#pragma once

enum TokenType {
    // PUNCTUATION
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_CURLY,
    RIGHT_CURLY,
    SEMICOLON,
    // MATH
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MOD,
    SINGLE_EQUAL,
    DOUBLE_EQUAL,
    NOT_EQUAL,
    NOT,
    MORE_THAN,
    MORE_THAN_EQUAL,
    LESS_THAN,
    LESS_THAN_EQUAL,
    AND,
    OR,
    CONST,
    // STMTS and VAR
    ALPHANUM,
    EMPTY,
};