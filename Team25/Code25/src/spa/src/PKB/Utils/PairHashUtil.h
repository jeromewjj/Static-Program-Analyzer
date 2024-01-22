#include <functional>
#include <utility>

#ifndef SPA_PAIRHASHUTIL_H
#define SPA_PAIRHASHUTIL_H

template <typename T1, typename T2> struct PairHash {
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        std::hash<T1> hashT1;
        std::hash<T2> hashT2;

        // Combine the hash values of the individual elements using a simple hash combiner
        return hashT1(p.first) ^ (hashT2(p.second) << 1);
    }
};

#endif // SPA_PAIRHASHUTIL_H
