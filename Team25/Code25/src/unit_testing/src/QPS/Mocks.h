#include <algorithm>

#include "PKB/Interfaces/PKBReader.h"
#include "QPS/Clause/CondClause.h"
#include "QPS/Declaration/Declaration.h"
#include "QPS/Evaluator/Action/Action.h"
#include "QPS/Evaluator/Action/Strategy/ResultStrategy.h"
#pragma once

#ifndef MOCKS_H
#define MOCKS_H

using PatAssignStmt = std::pair<std::string, std::vector<std::string>>;
namespace Mock {
    class MockPKBReaderEntity : public PKBReaderEntityI {
        std::unordered_map<StatementType, std::unordered_set<int>> map = {
            {READ, {1, 2, 3}}, {PRINT, {4, 5}}, {ASSIGN, {6, 7, 8}}, {CALL, {9}}, {WHILE, {10}}, {IF, {11, 12, 13}}};

    public:
        VariableSet getVariables() const override {
            return {"v_x", "v_y", "v_z"};
        };
        ConstantSet getConstants() const override {
            return {"c_1", "c_2", "c_3"};
        };
        ProcedureSet getProcedures() const override {
            return {"p_x", "p_y", "p_z"};
        };
        StatementSet getStmtNum(StatementType type) const override {
            return map.at(type);
        };
        StatementSet getAllStmtNum() const override {
            return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
        };
    };
    class MockPKBReader : public PKBReader {
        std::unordered_map<StatementType, std::unordered_set<int>> map = {
            {READ, {1, 2, 3}}, {PRINT, {4, 5}}, {ASSIGN, {6, 7, 8}}, {CALL, {9}}, {WHILE, {10}}, {IF, {11, 12, 13}}};
        std::unordered_map<AbstractionType, std::unordered_set<std::pair<int, int>>> intAbsMap = {
            {AbstractionType::FOLLOWS, {{1, 2}, {2, 3}, {3, 4}}},
            {AbstractionType::FOLLOWS_T, {{1, 2}, {2, 3}, {3, 4}, {1, 3}, {2, 4}, {1, 4}}},
            {AbstractionType::NEXT, {{1, 2}, {2, 3}, {3, 4}}},
            {AbstractionType::NEXT_T, {{1, 2}, {2, 3}, {3, 4}, {1, 3}, {2, 4}, {1, 4}}},
            {AbstractionType::PARENTS, {{4, 5}, {5, 6}, {5, 7}, {7, 8}}},
            {AbstractionType::PARENTS_T, {{5, 6}, {5, 7}, {7, 8}, {5, 8}}},
            {AbstractionType::AFFECTS, {{4, 5}, {5, 6}, {5, 7}, {7, 8}}}};
        std::unordered_map<AbstractionType, std::unordered_set<std::pair<int, std::string>>> intexprMap = {
            {AbstractionType::MODIFIES, {{1, "v_x"}, {2, "v_z"}, {3, "v_y"}}},
            {AbstractionType::USES, {{2, "v_x"}, {3, "v_x"}}}};
        std::unordered_map<AbstractionType, std::unordered_set<std::pair<std::string, std::string>>> exprexprMap = {
            {AbstractionType::MODIFIES, {{"p_x", "v_x"}, {"p_x", "v_z"}, {"p_x", "v_y"}}},
            {AbstractionType::USES, {{"p_x", "v_x"}, {"p_x", "v_x"}}}};

    public:
        VariableSet getVariables() const override {
            return {"v_x", "v_y", "v_z"};
        };
        ConstantSet getConstants() const override {
            return {"c_1", "c_2", "c_3"};
        };
        ProcedureSet getProcedures() const override {
            return {"p_x", "p_y", "p_z"};
        };
        StatementSet getStmtNum(StatementType type) const override {
            return map.at(type);
        };
        StatementSet getAllStmtNum() const override {
            return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
        };
        bool containFollowsRelation(StmtNum followee, StmtNum follower) const override {
            return intAbsMap.at(AbstractionType::FOLLOWS).count(std::pair(followee, follower)) == 1;
        };
        bool containFollowsStarRelation(StmtNum followee, StmtNum follower) const override {
            return intAbsMap.at(AbstractionType::FOLLOWS_T).count(std::pair(followee, follower)) == 1;
        };
        // Check if specific Follows Relationship exist
        bool containFollowsRelation(Argument firstArg, Argument secondArg) const override;
        // Check if specific Follows star Relationship exist
        bool containFollowsStarRelation(Argument firstArg, Argument secondArg) const override;
        bool containParentRelation(StmtNum parent, StmtNum child) const override {
            return intAbsMap.at(AbstractionType::PARENTS).count(std::pair(parent, child)) == 1;
        };
        bool containParentStarRelation(StmtNum parent, StmtNum child) const override {
            return intAbsMap.at(AbstractionType::PARENTS_T).count(std::pair(parent, child)) == 1;
        };
        // Check if specific Parent Relationship exist
        bool containParentRelation(Argument firstArg, Argument secondArg) const override;
        // Check if specific Parent star Relationship exist
        bool containParentStarRelation(Argument firstArg, Argument secondArg) const override;
        bool containStmtUsesRelation(StmtNum stmtNum, Variable var) const override {
            return intexprMap.at(AbstractionType::USES).count(std::pair(stmtNum, var)) == 1;
        };
        bool containProcUsesRelation(Procedure proc, Variable var) const override {
            return exprexprMap.at(AbstractionType::USES).count(std::pair(proc, var)) == 1;
        };
        bool containStmtUsesRelation(Argument firstArg, Argument secondArg) const override;
        // Check if specific Procedure Uses Relationship exist
        bool containProcUsesRelation(Argument firstArg, Argument secondArg) const override;
        bool containStmtModifiesRelation(StmtNum stmtNum, Variable var) const override {
            return intexprMap.at(AbstractionType::MODIFIES).count(std::pair(stmtNum, var)) == 1;
        };
        bool containProcModifiesRelation(Procedure proc, Variable var) const override {
            return exprexprMap.at(AbstractionType::MODIFIES).count(std::pair(proc, var)) == 1;
        };
        // Check if specific Statement Modifies Relationship exist
        bool containStmtModifiesRelation(Argument firstArg, Argument secondArg) const override;
        // Check if specific Procedure Modifies Relationship exist
        bool containProcModifiesRelation(Argument firstArg, Argument secondArg) const override;
        bool containAssignPattern(StmtNum stmtNum, Argument firstArg, Argument secondArg) const override;

        bool containIfPattern(const StmtNum stmtNum, Argument firstArg) const override;
        bool containWhilePattern(const StmtNum stmtNum, Argument firstArg) const override;

        bool containNextRelation(Argument firstArg, Argument secondArg) const override;
        bool containNextStarRelation(Argument firstArg, Argument secondArg) const override;

        bool containAffectRelation(Argument firstArg, Argument secondArg) const override;

        // for attributes

        Procedure getProcedureCalledByStmt(StmtNum stmtNum) const override;
        VariableSet getVarsModifiedByStmt(StmtNum stmtNum) const override;
        VariableSet getVarsUsedByStmt(StmtNum stmtNum) const override;
        MockPKBReader(PKB pkb) : PKBReader(pkb){};
    };
    extern std::vector<Declaration> Declarations();
    class CounterAction : public Action {
        int counter;

    public:
        explicit CounterAction(Action& action) : Action(action), counter(0){};
        void doAction() override;
    };
    class MockResultStrategy : public ResultStrategy {
        void write(const PKBReader& reader, Context& context) override;
        bool tryShortCircuit(const PKBReader& reader, Context& context) override;
        void defaultWrite(Context& context) override;
    };
    class MockFalseStrategy : public ClauseStrategy {
        bool execute(const PKBReader& reader, const Context& context) override;
    };
    class MockTrueStrategy : public ClauseStrategy {
        bool execute(const PKBReader& reader, const Context& context) override;
    };
}

#endif // MOCKS_H