#include <utility>
#include <vector>

#include "Argument.h"

struct Tuple : Argument {
    std::vector<Argument> tupleItems;

    explicit Tuple(std::vector<Argument>& tupleItems_, std::string tupleStr)
        : Argument(ArgType::TUPLE, std::move(tupleStr)), tupleItems(tupleItems_){};
    std::vector<std::string> getSynonyms() override;
    std::vector<std::string> getAttrRefs() override;
    std::vector<Argument> getArguments() override;
    std::vector<Argument> getTupleItems();
};
