#include "PKB/Stores/CFGStore.h"
#include "catch.hpp"

/**
 * CFG Build is based on this program
 *
 * procedure Second {
    01        x = 0;
    02        i = 5;
    03        while (i!=0) {
    04            x = x + 2*y;
    05            call Third;
    06            i = i - 1; }
    07        if (x==1) then {
    08            x = x+1; }
              else {
    09            z = 1; }
    10        z = z + x + i;
    11        y = z + 2;
    12        x = x * y + z; }

 */

TEST_CASE("Test CFGStore - generate Next Relationship") {
    CFGStore cfgStore;
    CFGStore::CFGBlockSet cfgSet = {
        {1, "Second", CFGBlockType::START_PROC, {1, 2}, {2}}, {2, "Second", CFGBlockType::NORMAL, {3}, {3, 4}},
        {3, "Second", CFGBlockType::NORMAL, {4, 5, 6}, {2}},  {4, "Second", CFGBlockType::DUMMY, {}, {5}},
        {5, "Second", CFGBlockType::NORMAL, {7}, {6, 7}},     {6, "Second", CFGBlockType::NORMAL, {8}, {8}},
        {7, "Second", CFGBlockType::NORMAL, {9}, {8}},        {8, "Second", CFGBlockType::NORMAL, {10, 11, 12}, {9}},
        {9, "Second", CFGBlockType::DUMMY, {}, {}},
    };
    cfgStore.setCfg(cfgSet);

    CFGStore::NextSet expectedResult = {{1, 2}, {2, 3}, {3, 4},  {3, 7},  {4, 5},   {5, 6},  {6, 3},
                                        {7, 8}, {7, 9}, {8, 10}, {9, 10}, {10, 11}, {11, 12}};
    CFGStore::NextSet actualResult = cfgStore.generateNextRelation();
    REQUIRE(actualResult == expectedResult);
}
