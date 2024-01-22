
#include "ClauseStrategy.h"

#include "QPS/Evaluator/PKBReaderHandler/AbstractionHandler.h"
#include "QPS/Evaluator/PKBReaderHandler/AttributeHandler.h"
#include "QPS/Evaluator/PKBReaderHandler/PatternHandler.h"
#include "QPS/Evaluator/Util.h"

std::string stripQuotes(const std::string& input);

std::string processAttrRef(const PKBReader& reader, const Context& context, const Argument& arg) {
    auto res = EvalUtil::split(arg.str, EvalUtil::DOT);
    auto syn = res[0];
    auto attrRaw = res[1];
    const auto& e = context.synonymPos.at(syn);
    auto attr = Attribute::RAW_TO_ATTR.at(attrRaw);
    auto val = PKBAttribute::HANDLERS.at(attr)(reader, e);
    return val;
};

bool STStrategy::execute(const PKBReader& reader, const Context& context) {
    auto type = abstraction.type;
    auto args = abstraction.args;
    HandleOption option;
    std::string str1;
    if (args[0].type == ArgType::EXPRESSION) {
        str1 = stripQuotes(args[0].str);
        option.firstArgString = true;
    }
    else if (args[0].type == ArgType::CONSTANT) {
        str1 = args[0].str;
        option.firstArgString = false;
    }
    else if (args[0].type == ArgType::SYNONYM) {
        const auto& e1 = context.synonymPos.at(args[0].str);
        if (e1.number > 0) {
            str1 = std::to_string(e1.number);
            option.firstArgString = false;
        }
        else {
            str1 = e1.name;
            option.firstArgString = true;
        }
    }
    Argument arg1{args[0].type, str1};

    std::string str2;
    if (args[1].type == ArgType::EXPRESSION) {
        str2 = stripQuotes(args[1].str);
    }
    else if (args[1].type == ArgType::CONSTANT) {
        str2 = args[1].str;
    }
    else if (args[1].type == ArgType::SYNONYM) {
        const auto& e2 = context.synonymPos.at(args[1].str);
        if (e2.number > 0) {
            str2 = std::to_string(e2.number);
        }
        else {
            str2 = e2.name;
        }
    }
    Argument arg2{args[1].type, str2};

    return PKBAbstraction::HANDLERS.at(type)(reader, arg1, arg2, option);
}

bool PatStrategy::execute(const PKBReader& reader, const Context& context) {
    const auto& e1 = context.synonymPos.at(patternSynonym);

    std::string str2;
    if (args[0].type == ArgType::EXPRESSION) {
        str2 = args[0].str;
    }
    else if (args[0].type == ArgType::SYNONYM) {
        const auto& e2 = context.synonymPos.at(args[0].str);
        if (e2.number > 0) {
            str2 = std::to_string(e2.number);
        }
        else {
            str2 = e2.name;
        }
    }
    Argument arg2{args[0].type, str2};

    std::vector<Argument> vec{arg2};

    for (size_t i = 1; i < args.size(); i++) {
        vec.push_back(args[i]);
    }

    return PKBPattern::HANDLERS.at(e1.entityType)(reader, e1, vec);
}

bool NotStrategy::execute(const PKBReader& reader, const Context& context) {
    return !strategy->execute(reader, context);
}

bool WithStrategy::execute(const PKBReader& reader, const Context& context) {
    std::string leftVal = leftArg.str;
    if (leftArg.type == ArgType::ATTRREF) {
        leftVal = processAttrRef(reader, context, leftArg);
    }
    else if (leftArg.type == ArgType::EXPRESSION) {
        leftVal = stripQuotes(leftArg.str);
    }
    std::string rightVal = rightArg.str;
    if (rightArg.type == ArgType::ATTRREF) {
        rightVal = processAttrRef(reader, context, rightArg);
    }
    else if (rightArg.type == ArgType::EXPRESSION) {
        rightVal = stripQuotes(rightArg.str);
    }
    return leftVal == rightVal;
}
