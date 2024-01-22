#include "SemanticException.h"

SemanticException::SemanticException() : SpaException("SemanticError") {}

SemanticException::SemanticException(std::string_view exceptionMessage)
    : SpaException(std::string(exceptionMessage) + "SemanticError") {}

std::string_view SemanticException::what() {
    return "SemanticError";
}