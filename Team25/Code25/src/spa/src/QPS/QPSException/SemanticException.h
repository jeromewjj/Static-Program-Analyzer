#include "SpaException.h"

class SemanticException : public SpaException {
public:
    SemanticException();
    SemanticException(std::string_view exceptionMessage);
    std::string_view what();
};
