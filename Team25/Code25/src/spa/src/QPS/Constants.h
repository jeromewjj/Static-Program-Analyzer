#ifndef CONSTANTS_H
#define CONSTANTS_H
#pragma once
#include <regex>
#include <string>

namespace Constants {
    // Strings
    const std::string SPACE = " ";
    const std::string WHITESPACE = " \t\n\r\f\v";
    const std::string COMMA = ",";
    const std::string SEMICOLON = ";";
    const std::string UNDERSCORE = "_";
    const std::string OPEN_PARENTHESIS = "(";
    const std::string CLOSE_PARENTHESIS = ")";

    // Chars
    const char CHAR_UNDERSCORE = '_';
    const char CHAR_OPEN_PARENTHESIS = '(';
    const char CHAR_CLOSE_PARENTHESIS = ')';
    const char CHAR_COMMA = ',';
    const char CHAR_DOUBLE_QUOTE = '"';
    const char CHAR_MULTIPLY = '*';
    const char CHAR_DIVIDE = '/';
    const char CHAR_MOD = '%';
    const char CHAR_PLUS = '+';
    const char CHAR_MINUS = '-';
    const char CHAR_SINGLE_QUOTE = '\'';
    const char CHAR_DOT = '.';
    const char CHAR_OPEN_TUPLE = '<';
    const char CHAR_CLOSE_TUPLE = '>';
    const char CHAR_EQUAL = '=';

    // Regex Patterns
    const std::string IDENT_PATTERN = "[a-zA-Z][a-zA-Z0-9]*";
    const std::string INTEGER_PATTERN = "0|[1-9][0-9]*";
    const std::string NAME_PATTERN = "[a-zA-Z][a-zA-Z0-9]*";
    const std::string ENTITY_PATTERN = "^(stmt|read|print|call|while|if|assign|variable|constant|procedure)$";

    // Keywords
    const std::string SELECT_PATTERN = "Select";
    const std::string SUCH_PATTERN = "such";
    const std::string THAT_PATTERN = "that";
    const std::string FOLLOWS_PATTERN = "Follows";
    const std::string FOLLOWST_PATTERN = "Follows*";
    const std::string PARENT_PATTERN = "Parent";
    const std::string PARENTT_PATTERN = "Parent*";
    const std::string USES_PATTERN = "Uses";
    const std::string MODIFIES_PATTERN = "Modifies";
    const std::string CALLS_PATTERN = "Calls";
    const std::string CALLST_PATTERN = "Calls*";
    const std::string NEXT_PATTERN = "Next";
    const std::string NEXTT_PATTERN = "Next*";
    const std::string AFFECTS_PATTERN = "Affects";
    const std::string PATTERN_PATTERN = "pattern";
    const std::string BOOLEAN_PATTERN = "BOOLEAN";
    const std::string WITH_PATTERN = "with";
    const std::string AND_PATTERN = "and";
    const std::string NOT_PATTERN = "not";
    const std::string WHILE_PATTERN = "while";
    const std::string IF_PATTERN = "if";
    const std::string ASSIGN_PATTERN = "assign";

    // AttrName
    const std::string PROCNAME_PATTERN = "procName";
    const std::string VARNAME_PATTERN = "varName";
    const std::string VALUE_PATTERN = "value";
    const std::string STMTNO_PATTERN = "stmt#";
}

namespace ErrorMessage {
    extern const std::string INVALID_NUM_OF_ARGS;
    extern std::string INVALID_FIRST_ARG(const std::string& synonym);
    extern std::string INVALID_SECOND_ARG(const std::string& synonym);
    extern std::string INVALID_SYNONYM_TYPE(const std::string& expected);
    extern std::string INVALID_SYNONYM(const std::string& synonym);
    extern std::string INVALID_ARG(const std::string& synonym);
    extern std::string INVALID_SYNONYM_PAT(const std::string& synonym);
}
#endif // CONSTANTS_H