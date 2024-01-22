
#include "PatternHandler.h"

std::string stripUnderscore(const std::string& input) {
    std::string result = input.substr(1, input.size() - 2);
    return result;
}

std::string stripQuotes(const std::string& input) {
    std::string result = input.substr(1, input.size() - 2);
    return result;
}

const PKBPatternHandler ASSIGN_PAT_HANDLER = [](const PKBReader& reader, const Entity& e1,
                                                const std::vector<Argument>& args) {
    std::string str1 = args[0].str;
    if (args[0].type == ArgType::EXPRESSION) {
        str1 = stripQuotes(str1);
    }
    std::string str2 = args[1].str;
    if (args[1].type == ArgType::EXPRESSION) {
        str2 = stripQuotes(str2);
    }
    if (args[1].type == ArgType::WILDCARD_EXPR) {
        str2 = stripQuotes(stripUnderscore(str2));
    }
    return reader.containAssignPattern(e1.number, {args[0].type, str1}, {args[1].type, str2});
};

const PKBPatternHandler IF_PAT_HANDLER = [](const PKBReader& reader, const Entity& e1,
                                            const std::vector<Argument>& args) {
    std::string str1 = args[0].str;
    if (args[0].type == ArgType::EXPRESSION) {
        str1 = stripQuotes(str1);
    }
    return reader.containIfPattern(e1.number, {args[0].type, str1});
};

const PKBPatternHandler WHILE_PAT_HANDLER = [](const PKBReader& reader, const Entity& e1,
                                               const std::vector<Argument>& args) {
    std::string str1 = args[0].str;
    if (args[0].type == ArgType::EXPRESSION) {
        str1 = stripQuotes(str1);
    }
    return reader.containWhilePattern(e1.number, {args[0].type, str1});
};

namespace PKBPattern {
    const PKBPatternMap HANDLERS = {
        {EntityType::ASSIGN, ASSIGN_PAT_HANDLER},
        {EntityType::IF, IF_PAT_HANDLER},
        {EntityType::WHILE, WHILE_PAT_HANDLER},
    };
}
