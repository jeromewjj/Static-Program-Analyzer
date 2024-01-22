
#include "Constants.h"

namespace ErrorMessage {
    const std::string INVALID_NUM_OF_ARGS = "Wrong number of arguments: ";
    std::string INVALID_FIRST_ARG(const std::string& synonym) {
        return "Invalid first argument \"" + synonym + "\": ";
    };
    std::string INVALID_SECOND_ARG(const std::string& synonym) {
        return "Invalid second argument \"" + synonym + "\": ";
    };
    std::string INVALID_SYNONYM_TYPE(const std::string& expected) {
        return "Incorrect type of synonym (expected type: " + expected + "): ";
    }
    std::string INVALID_SYNONYM(const std::string& synonym) {
        return "No declaration match synonym \"" + synonym + "\": ";
    };
    std::string INVALID_ARG(const std::string& synonym) {
        return "Invalid argument for \"" + synonym + "\": ";
    }
    std::string INVALID_SYNONYM_PAT(const std::string& synonym) {
        return "Synonym \"" + synonym + "\" can't be used for pattern clauses: ";
    }
}