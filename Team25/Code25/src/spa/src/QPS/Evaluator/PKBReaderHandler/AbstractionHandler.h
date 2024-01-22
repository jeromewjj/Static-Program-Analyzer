
#ifndef SPA_ABSTRACTIONHANDLER_H
#define SPA_ABSTRACTIONHANDLER_H
#include <functional>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Abstraction/Abstraction.h"

struct HandleOption {
    bool firstArgString;
};

using PKBSTHandler = std::function<bool(const PKBReader&, const Argument&, const Argument&, const HandleOption&)>;
using PKBSTMap = std::unordered_map<AbstractionType, PKBSTHandler>;

namespace PKBAbstraction {
    extern const PKBSTMap HANDLERS;
}

#endif // SPA_ABSTRACTIONHANDLER_H
