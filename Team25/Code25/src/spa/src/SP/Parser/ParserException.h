#pragma once
#include <exception>
#include <utility>

class ParserException : public std::exception {
public:
    explicit ParserException(std::string message) : message(std::move(message)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};