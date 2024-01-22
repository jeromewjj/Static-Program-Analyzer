#pragma once
#include <iostream>
#include <string>

namespace helper {
    inline void ASSERT(bool b, std::string assertionMsg) {
        if (b) {
            throw std::runtime_error("ASSERTION_ERR: " + assertionMsg);
        }
    }
}