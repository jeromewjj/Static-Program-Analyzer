
#include "ResultStrategy.h"

const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";

std::string convertEntity(const Entity& e) {
    if (e.number != 0) {
        return std::to_string(e.number);
    }
    return e.name;
}

std::string processSynonym(Context& context, const Argument& arg) {
    const auto& e = context.synonymPos[arg.str];
    return convertEntity(e);
};

std::string processAttrRef(const PKBReader& reader, Context& context, const Argument& arg) {
    auto res = EvalUtil::split(arg.str, EvalUtil::DOT);
    auto syn = res[0];
    auto attrRaw = res[1];
    const auto& e = context.synonymPos[syn];
    auto attr = Attribute::RAW_TO_ATTR.at(attrRaw);
    auto val = PKBAttribute::HANDLERS.at(attr)(reader, e);
    return val;
};

void SingleResult::write(const PKBReader& reader, Context& context) {
    if (argument.type == ArgType::SYNONYM) {
        context.result.insert(processSynonym(context, argument));
        return;
    }
    if (argument.type == ArgType::ATTRREF) {
        context.result.insert(processAttrRef(reader, context, argument));
        return;
    }
}

bool SingleResult::tryShortCircuit(const PKBReader& reader, Context& context) {
    std::string res;
    if (argument.type == ArgType::SYNONYM) {
        res = processSynonym(context, argument);
    }
    if (argument.type == ArgType::ATTRREF) {
        res = processAttrRef(reader, context, argument);
    }
    return context.result.count(res) == 1;
}

void BooleanResult::write(const PKBReader& reader, Context& context) {
    context.result.insert(TRUE);
}

void BooleanResult::defaultWrite(Context& context) {
    context.result.insert(FALSE);
}

void TupleResult::write(const PKBReader& reader, Context& context) {
    std::string res;
    for (size_t i = 0; i < arguments.size(); i++) {
        std::string val;
        if (arguments[i].type == ArgType::SYNONYM) {
            val = processSynonym(context, arguments[i]);
        }
        if (arguments[i].type == ArgType::ATTRREF) {
            val = processAttrRef(reader, context, arguments[i]);
        }
        if (i != 0) {
            res.append(" ");
        }
        res.append(val);
    }
    context.result.insert(res);
}

bool TupleResult::tryShortCircuit(const PKBReader& reader, Context& context) {
    std::string res;
    for (size_t i = 0; i < arguments.size(); i++) {
        std::string val;
        if (arguments[i].type == ArgType::SYNONYM) {
            val = processSynonym(context, arguments[i]);
        }
        if (arguments[i].type == ArgType::ATTRREF) {
            val = processAttrRef(reader, context, arguments[i]);
        }
        if (i != 0) {
            res.append(" ");
        }
        res.append(val);
    }
    return context.result.count(res) == 1;
}

bool ResultStrategy::tryShortCircuit(const PKBReader& reader, Context& context) {
    return false;
}
