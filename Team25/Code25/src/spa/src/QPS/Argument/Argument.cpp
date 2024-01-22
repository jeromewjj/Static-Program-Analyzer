#include "Argument.h"

const char DOT = '.';

std::string getSyn(const std::string& str) {
    auto i = str.find(DOT);
    return str.substr(0, i);
}

bool Argument::operator==(const Argument& other) const {
    if (type == ArgType::WILDCARD) {
        return other.type == ArgType::WILDCARD;
    }
    return type == other.type && str == other.str;
}

ArgType Argument::getType() {
    return type;
}

std::string Argument::getStr() {
    return str;
}

std::vector<std::string> Argument::getSynonyms() {
    if (type == ArgType::ATTRREF) {
        return {getSyn(str)};
    }
    if (type == ArgType::SYNONYM) {
        return {str};
    }
    return {};
}

std::vector<std::string> Argument::getAttrRefs() {
    if (type == ArgType::ATTRREF) {
        return {str};
    }
    return {};
}

std::vector<Argument> Argument::getArguments() {
    return {{type, str}};
}
