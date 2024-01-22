#include "SyntacticException.h"

SyntacticException::SyntacticException() : SpaException("SyntacticError") {}

SyntacticException::SyntacticException(std::string_view exceptionMessage)
    : SpaException(std::string(exceptionMessage) + "SyntacticError") {}

std::string_view SyntacticException::what() {
    return "SyntaxError";
}
