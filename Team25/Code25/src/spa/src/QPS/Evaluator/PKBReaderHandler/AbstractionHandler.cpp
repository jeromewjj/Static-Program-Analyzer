
#include "AbstractionHandler.h"

const PKBSTHandler followsHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                       const HandleOption& option) {
    return reader.containFollowsRelation(e1, e2);
};
const PKBSTHandler followsTHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                        const HandleOption& option) {
    return reader.containFollowsStarRelation(e1, e2);
};
const PKBSTHandler parentsHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                       const HandleOption& option) {
    return reader.containParentRelation(e1, e2);
};
const PKBSTHandler parentsTHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                        const HandleOption& option) {
    return reader.containParentStarRelation(e1, e2);
};
const PKBSTHandler callsHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                     const HandleOption& option) {
    return reader.containCallsRelation(e1, e2);
};
const PKBSTHandler callsTHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                      const HandleOption& option) {
    return reader.containCallsStarRelation(e1, e2);
};
const PKBSTHandler nextHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                    const HandleOption& option) {
    return reader.containNextRelation(e1, e2);
};
const PKBSTHandler nextTHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                     const HandleOption& option) {
    return reader.containNextStarRelation(e1, e2);
};
const PKBSTHandler modifiesHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                        const HandleOption& option) {
    if (option.firstArgString) {
        return reader.containProcModifiesRelation(e1, e2);
    }
    return reader.containStmtModifiesRelation(e1, e2);
};
const PKBSTHandler usesHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                    const HandleOption& option) {
    if (option.firstArgString) {
        return reader.containProcUsesRelation(e1, e2);
    }
    return reader.containStmtUsesRelation(e1, e2);
};
const PKBSTHandler affectsHandler = [](const PKBReader& reader, const Argument& e1, const Argument& e2,
                                       const HandleOption& option) {
    return reader.containAffectRelation(e1, e2);
};
namespace PKBAbstraction {
    const PKBSTMap HANDLERS = {
        {AbstractionType::FOLLOWS, followsHandler},   {AbstractionType::FOLLOWS_T, followsTHandler},
        {AbstractionType::PARENTS, parentsHandler},   {AbstractionType::PARENTS_T, parentsTHandler},
        {AbstractionType::CALLS, callsHandler},       {AbstractionType::CALLS_T, callsTHandler},
        {AbstractionType::NEXT, nextHandler},         {AbstractionType::NEXT_T, nextTHandler},
        {AbstractionType::MODIFIES, modifiesHandler}, {AbstractionType::USES, usesHandler},
        {AbstractionType::AFFECTS, affectsHandler}};
}
