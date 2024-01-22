#include <sstream>
#include <vector>

#ifndef SPA_UTIL_H
#define SPA_UTIL_H
namespace EvalUtil {
    const char DOT = '.';
    std::vector<std::string> split(const std::string& str, char delimiter);
}
#endif // SPA_UTIL_H
