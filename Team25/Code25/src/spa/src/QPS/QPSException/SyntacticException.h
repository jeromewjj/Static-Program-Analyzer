#ifndef SYNTACTICEXCEPTION_H
#define SYNTACTICEXCEPTION_H

#include "SpaException.h"

class SyntacticException : public SpaException {
public:
    SyntacticException();
    SyntacticException(std::string_view exceptionMessage);
    std::string_view what();
};

#endif