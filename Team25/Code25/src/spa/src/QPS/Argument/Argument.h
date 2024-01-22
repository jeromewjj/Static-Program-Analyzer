#include <string>
#include <utility>
#include <vector>

#ifndef SPA_ARGUMENT_H
#define SPA_ARGUMENT_H

enum class ArgType {
    SYNONYM,
    EXPRESSION,
    WILDCARD,
    WILDCARD_EXPR,
    CONSTANT,
    ATTRREF,
    TUPLE,
    BOOLEAN,
};

/**
 * @brief Represents an argument in a program.
 *
 * An argument can have different types, such as SYNONYM, EXPRESSION, WILDCARD,
 * or WILDCARD_EXPR, and it contains a string associated with the argument.
 *
 * @param type The type of the argument (e.g., SYNONYM, EXPRESSION).
 * @param str The string value associated with the argument.
 *            Note that the constructor moves the provided string into
 *            the 'str' member, optimizing performance by avoiding unnecessary copies.
 */
struct Argument {
    // Note that Argument constructor move string
    Argument(ArgType type_, std::string str_) : type(type_), str(std::move(str_)){};
    const ArgType type;
    const std::string str;
    bool operator==(const Argument& other) const;
    virtual std::vector<std::string> getSynonyms();
    virtual std::vector<std::string> getAttrRefs();
    virtual std::vector<Argument> getArguments();
    ArgType getType();
    std::string getStr();
};

#endif // SPA_ARGUMENT_H
