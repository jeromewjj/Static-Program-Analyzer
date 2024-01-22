#ifndef SPAEXCEPTION_H
#define SPAEXCEPTION_H

#include <iostream>
#include <string>

class SpaException : public std::exception {
public:
    SpaException() = default;
    SpaException(std::string_view exceptionMessage) : exceptionMessage(exceptionMessage){};
    virtual std::string_view what() = 0;

protected:
    std::string exceptionMessage;
};

#endif