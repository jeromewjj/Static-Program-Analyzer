#pragma once
#include "./QPS/Argument/Argument.h"

struct AttrCompare {
    Argument leftArg;
    Argument rightArg;

    AttrCompare(Argument leftArg_, Argument rightArg_) : leftArg(leftArg_), rightArg(rightArg_){};
};
