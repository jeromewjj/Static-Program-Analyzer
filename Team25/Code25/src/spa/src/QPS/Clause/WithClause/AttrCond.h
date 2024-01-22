#include <vector>

#include "AttrCompare.h"

struct AttrCond {
    std::vector<AttrCompare> listOfAttrCompare;

    AttrCond(AttrCompare listOfAttrCompare_) : listOfAttrCompare(listOfAttrCompare){};
};