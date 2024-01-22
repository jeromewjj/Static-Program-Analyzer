#pragma once

#include <iostream>
#include <memory>
#include <unordered_set>

#include "SP/DesignExtraction/PKBAdapter.h"

// forward declaration to prevent dependency on ASTNode.h
// which would have otherwise created circular dependency
class VariableNode;
class ConstantNode;
class StatementNode;
class ProcedureNode;
class CallNode;
class AssignNode;
class IfThenElseNode;
class WhileThenNode;

class ExtractEntityVisitor {
public:
    explicit ExtractEntityVisitor(std::shared_ptr<PKBAdapter> pkbAdapter)
        : pkbAdapter(pkbAdapter), vars(std::make_shared<std::unordered_set<std::string>>()),
          consts(std::make_shared<std::unordered_set<std::string>>()),
          procedures(std::make_shared<std::unordered_set<std::string>>()),
          procAndCallingStmts(std::make_shared<std::unordered_map<string, std::unordered_set<int>>>()),
          assignInfo(std::make_shared<std::vector<PKB_ASSIGN>>()),
          ifConditionalVarsMap(std::make_shared<std::unordered_map<int, std::unordered_set<string>>>()),
          whileConditionalVarsMap(std::make_shared<std::unordered_map<int, std::unordered_set<string>>>()) {}

    virtual void extractEntity(const std::shared_ptr<const VariableNode>& node) const;
    virtual void extractEntity(const std::shared_ptr<const ConstantNode>& node) const;
    virtual void extractEntity(const std::shared_ptr<const ProcedureNode>& node) const;
    virtual void extractEntity(const std::shared_ptr<const CallNode>& node) const;
    virtual void extractEntity(const std::shared_ptr<const AssignNode>& node) const;
    virtual void extractEntity(const std::shared_ptr<const IfThenElseNode>& node) const;
    virtual void extractEntity(const std::shared_ptr<const WhileThenNode>& node) const;

    std::unordered_set<std::string> getVars() {
        return *vars;
    }
    std::unordered_set<std::string> getConsts() {
        return *consts;
    }
    std::unordered_set<std::string> getProcedures() {
        return *procedures;
    }
    std::unordered_map<std::string, std::unordered_set<int>> getProcAndCallingStmts() {
        return *procAndCallingStmts;
    }
    std::vector<PKB_ASSIGN> getAssignInfo() {
        return *assignInfo;
    }
    std::unordered_map<int, std::unordered_set<string>> getIfCondVars() {
        return *ifConditionalVarsMap;
    }
    std::unordered_map<int, std::unordered_set<string>> getWhileCondVars() {
        return *whileConditionalVarsMap;
    }

    void flushData() {
        pkbAdapter->setVariables(*vars);
        vars->clear();

        pkbAdapter->setConstants(*consts);
        consts->clear();

        pkbAdapter->setProcedures(*procedures);
        procedures->clear();

        pkbAdapter->setCallsToProcedure(procAndCallingStmts);
        procAndCallingStmts->clear();

        pkbAdapter->setAssignPatterns(*assignInfo);
        assignInfo->clear();

        pkbAdapter->setIfConditionalVariables(ifConditionalVarsMap);
        ifConditionalVarsMap->clear();

        pkbAdapter->setWhileConditionalVariables(whileConditionalVarsMap);
        whileConditionalVarsMap->clear();
    }

private:
    void addVar(const std::string& varName) const {
        vars->insert(varName);
    }
    void addConst(const std::string& constVal) const {
        consts->insert(constVal);
    }
    void addProcedure(const std::string& procName) const {
        procedures->insert(procName);
    }
    void addAssignInfo(const int stmtNum, const std::string var, const std::string exactExpression,
                       const std::unordered_set<std::string>& partialExpressions) const {
        assignInfo->push_back({stmtNum, var, exactExpression, partialExpressions});
    }

    const std::shared_ptr<std::unordered_set<std::string>> vars;
    const std::shared_ptr<std::unordered_set<std::string>> consts;
    const std::shared_ptr<std::unordered_set<std::string>> procedures;
    // vector type chosen as there is no need to filter out duplicate values or
    // lookup elems vectors compared to sets have faster insertion & iteration,
    // and less memory overhead
    const std::shared_ptr<std::vector<PKB_ASSIGN>> assignInfo;
    const std::shared_ptr<std::unordered_map<int, std::unordered_set<string>>> ifConditionalVarsMap;
    const std::shared_ptr<std::unordered_map<int, std::unordered_set<string>>> whileConditionalVarsMap;
    const std::shared_ptr<std::unordered_map<string, std::unordered_set<int>>> procAndCallingStmts;

    const std::shared_ptr<PKBAdapter> pkbAdapter;
};
