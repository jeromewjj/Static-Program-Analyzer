
#include "Util.h"

std::vector<std::string> EvalUtil::split(const std::string& str, char delimiter) {
    std::stringstream s(str);
    std::string token;
    std::vector<std::string> res;

    while (std::getline(s, token, delimiter)) {
        res.push_back(token);
    }

    return res;
}
