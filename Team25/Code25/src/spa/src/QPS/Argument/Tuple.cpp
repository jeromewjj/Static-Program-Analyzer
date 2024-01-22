#include "Tuple.h"

const char DOT_ = '.';

std::string getSynn(const std::string& str) {
    auto i = str.find(DOT_);
    return str.substr(0, i);
}

std::vector<std::string> Tuple::getSynonyms() {
    std::vector<std::string> res;
    for (const auto& arg : tupleItems) {
        if (arg.type == ArgType::ATTRREF) {
            res.push_back(getSynn(arg.str));
            continue;
        }
        res.push_back(arg.str);
    }
    return res;
}

std::vector<Argument> Tuple::getTupleItems() {
    return tupleItems;
}

std::vector<std::string> Tuple::getAttrRefs() {
    std::vector<std::string> res;
    for (const auto& arg : tupleItems) {
        if (arg.type == ArgType::ATTRREF) {
            res.push_back(arg.str);
            continue;
        }
    }
    return res;
}

std::vector<Argument> Tuple::getArguments() {
    return tupleItems;
}
