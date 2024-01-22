#include "PKB/Interfaces/PKBWriter.h"
#include "PKB/PKB.h"
#include "catch.hpp"

/**
 * Program is based on this program
 *
 * procedure Second {
    01        x = 0;
    02        i = 5;
    03        while (i!=0) {
    04            x = x + 2*y;
    05            read k;
    06            i = i - 1; }
    07        if (x==1) then {
    08            x = x+1; }
              else {
    09            z = 1; }
    10        z = z + x + i;
    11        y = z + 2;
    12        x = x * y + z; }

 */

TEST_CASE("Test PKB - Generate Affect Relationship") {
    PKB pkb;
    auto pkbWriter = PKBWriter(pkb);

    PKBWriter::CFGBlockSet cfgSet = {
        {1, "Second", CFGBlockType::START_PROC, {1, 2}, {2}},    {2, "Second", CFGBlockType::WHILE, {3}, {3, 4}},
        {3, "Second", CFGBlockType::NORMAL, {4, 5, 6}, {2}},     {4, "Second", CFGBlockType::IF, {7}, {5, 6}},
        {5, "Second", CFGBlockType::NORMAL, {8}, {7}},           {6, "Second", CFGBlockType::NORMAL, {9}, {7}},
        {7, "Second", CFGBlockType::END_PROC, {10, 11, 12}, {}},
    };

    pkbWriter.setCfg(cfgSet);

    PKBWriter::StmtUsesSet useSet = {
        {3, "i"},  {3, "x"},  {3, "y"},  {4, "x"},  {4, "y"},  {6, "i"},  {7, "x"},  {8, "x"},
        {11, "z"}, {10, "i"}, {10, "x"}, {10, "z"}, {12, "x"}, {12, "y"}, {12, "z"},
    };
    pkbWriter.setStatementUsesRelationship(useSet);

    PKBWriter::StmtModifiesSet modifiedSet = {
        {1, "x"}, {2, "i"}, {3, "i"}, {3, "k"}, {3, "x"},  {4, "x"},  {5, "k"},  {6, "i"},
        {7, "x"}, {7, "z"}, {8, "x"}, {9, "z"}, {10, "z"}, {11, "y"}, {12, "x"},
    };
    pkbWriter.setStatementModifiesRelationship(modifiedSet);

    PKBWriter::StatementSet stmtSet = {
        {StatementType::ASSIGN, 1},  {StatementType::ASSIGN, 2},  {StatementType::WHILE, 3},
        {StatementType::ASSIGN, 4},  {StatementType::READ, 5},    {StatementType::ASSIGN, 6},
        {StatementType::IF, 7},      {StatementType::ASSIGN, 8},  {StatementType::ASSIGN, 9},
        {StatementType::ASSIGN, 10}, {StatementType::ASSIGN, 11}, {StatementType::ASSIGN, 12}};
    pkbWriter.setStatements(stmtSet);

    PKB::AffectSet expectedResult = {
        {1, 4},  {1, 8}, {1, 10}, {1, 12}, {2, 6},  {2, 10}, {4, 4},   {4, 8},   {4, 10},
        {4, 12}, {6, 6}, {6, 10}, {8, 10}, {8, 12}, {9, 10}, {10, 11}, {10, 12}, {11, 12},
    };

    PKB::AffectSet actualResult = pkb.generateAffectRelation();

    REQUIRE(actualResult == expectedResult);
}