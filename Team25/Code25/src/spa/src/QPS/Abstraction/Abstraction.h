#include <utility>
#include <vector>

#include "QPS/Argument/Argument.h"
#include "QPS/Declaration/Declaration.h"
#ifndef SPA_ABSTRACTION_H
#define SPA_ABSTRACTION_H

enum class AbstractionType {
    MODIFIES,
    USES,
    FOLLOWS,
    FOLLOWS_T,
    PARENTS,
    PARENTS_T,
    CALLS,
    CALLS_T,
    NEXT,
    NEXT_T,
    AFFECTS,
};

/**
 * @brief Represents an abstraction in a program.
 *
 * An abstraction is a higher-level construct that contains information about
 * its type and a vector of arguments.
 *
 * @param type The type of the abstraction.
 * @param args The vector of arguments associated with the abstraction.
 *             Note that the constructor moves the provided arguments into
 *             the 'args' member, optimizing performance by avoiding unnecessary
 *             copies.
 */
struct Abstraction {
    // Note that constructor moves the arguments
    Abstraction(AbstractionType type_, std::vector<Argument> args_) : type(type_), args(std::move(args_)){};
    std::vector<Argument> args;
    AbstractionType type;

    bool operator==(const Abstraction& other) const {
        return type == other.type && args == other.args;
    }
};

#endif // SPA_ABSTRACTION_H
