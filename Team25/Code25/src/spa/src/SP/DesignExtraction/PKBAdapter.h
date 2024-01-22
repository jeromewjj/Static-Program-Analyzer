#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::unordered_set;
using std::vector;

#include "PKB/Interfaces/PKBWriter.h"
#include "PKB/Types/CFGType.h"
#include "PKB/Types/EntityType.h"
#include "PKB/Types/PatternType.h"
#include "PKB/Types/StatementType.h"
#include "SP/AST/NodeType.h"

using PKB_STATEMENT = EntityTypes::STATEMENT;
using PKB_ASSIGN = Assign;
class PKBAdapter {
public:
    explicit PKBAdapter(PKBWriter pkbWriter) : pkbWriter(pkbWriter) {}

    static std::shared_ptr<PKBAdapter> getEmptyPKBAdapter() {
        PKB pkb{};
        PKBWriter pkbWriter{pkb};
        auto pkbAdapter = std::make_shared<PKBAdapter>(pkbWriter);
        return pkbAdapter;
    }

    // ENTITIES ---
    void setVariables(std::unordered_set<std::string>& vars) const {
        pkbWriter.setVariables(vars);
    }

    void setConstants(std::unordered_set<std::string>& consts) const {
        pkbWriter.setConstants(consts);
    }

    void setProcedures(std::unordered_set<std::string>& procedures) const {
        pkbWriter.setProcedures(procedures);
    }

    void setStatements(std::vector<std::pair<NodeType, int>>& stmts) const {
        std::unordered_set<PKB_STATEMENT> pkbStmts{};
        for (const auto& stmt : stmts) {
            pkbStmts.insert(createPKBStatment(stmt.first, stmt.second));
        }
        pkbWriter.setStatements(pkbStmts);
    }

    /**
     * @example partialSet `unordered_set<string> like {"y", "z", "y+z"}
     * @example assignInfoSet `PKB_ASSIGN like {1, "x", "y+z", partialSet}`
     */
    void setAssignPatterns(std::vector<PKB_ASSIGN> assignInfoSet) const {
        pkbWriter.setAssignPatterns({assignInfoSet.begin(), assignInfoSet.end()});
    }

    void setCallsToProcedure(
        const std::shared_ptr<std::unordered_map<std::string, std::unordered_set<int>>> procToCallingStmtsMap) const {
        const auto procNameAndCallingStmtSet = std::make_shared<std::unordered_set<std::pair<string, int>>>();
        for (const auto& p : *procToCallingStmtsMap) {
            auto procName = p.first;
            auto stmtNums = p.second;
            for (const int& stmtNum : stmtNums) {
                procNameAndCallingStmtSet->insert({procName, stmtNum});
            }
        }
        pkbWriter.setCallsStmtRelationship(*procNameAndCallingStmtSet);
    }

    void setIfConditionalVariables(
        const std::shared_ptr<std::unordered_map<int, std::unordered_set<string>>>& ifConditionalVarsMap) const {
        const auto ifStmtConditionalVars = std::make_shared<std::unordered_set<std::pair<int, string>>>();
        for (const auto& x : *ifConditionalVarsMap) {
            auto stmt = x.first;
            auto vars = x.second;
            for (const string& v : vars) {
                ifStmtConditionalVars->insert({stmt, v});
            }
        }
        pkbWriter.setIfStatements(*ifStmtConditionalVars);
    }

    void setWhileConditionalVariables(
        const std::shared_ptr<std::unordered_map<int, std::unordered_set<string>>>& whileConditionalVarsMap) const {
        const auto whileStmtConditionalVars = std::make_shared<std::unordered_set<std::pair<int, string>>>();
        for (const auto& x : *whileConditionalVarsMap) {
            auto stmt = x.first;
            auto vars = x.second;
            for (const string& v : vars) {
                whileStmtConditionalVars->insert({stmt, v});
            }
        }
        pkbWriter.setWhileStatements(*whileStmtConditionalVars);
    }

    // RELATIONS---
    void setParentsRelationship(const std::shared_ptr<std::unordered_set<std::pair<int, int>>>& pairs) const {
        pkbWriter.setParentsRelationship(*pairs);
    }

    void setFollowsRelationship(const std::shared_ptr<std::unordered_set<std::pair<int, int>>>& pairs) const {
        pkbWriter.setFollowsRelationship(*pairs);
    }

    void
    setStatementUsesRelationship(const std::unordered_map<int, std::unordered_set<std::string>>& stmtVarsMap) const {
        const auto stmtVarPairs = std::make_shared<std::unordered_set<std::pair<int, std::string>>>();
        for (const auto& stmtVars : stmtVarsMap) {
            auto stmt = stmtVars.first;
            auto vars = stmtVars.second;
            for (const auto& var : vars) {
                stmtVarPairs->insert({stmt, var});
            }
        }
        pkbWriter.setStatementUsesRelationship(*stmtVarPairs);
    }

    void setProcedureUsesRelationship(
        const std::unordered_map<std::string, std::unordered_set<std::string>>& procVarsMap) const {
        const auto procVarPairs = std::make_shared<std::unordered_set<std::pair<std::string, std::string>>>();
        for (const auto& procVars : procVarsMap) {
            auto proc = procVars.first;
            auto vars = procVars.second;
            for (const auto& var : vars) {
                procVarPairs->insert({proc, var});
            }
        }
        pkbWriter.setProcedureUsesRelationship(*procVarPairs);
    }

    void setStatementModifiesRelationship(
        const std::unordered_map<int, std::unordered_set<std::string>>& stmtVarsMap) const {
        const auto stmtVarPairs = std::make_shared<std::unordered_set<std::pair<int, std::string>>>();
        for (const auto& stmtVars : stmtVarsMap) {
            auto stmt = stmtVars.first;
            auto vars = stmtVars.second;
            for (const auto& var : vars) {
                stmtVarPairs->insert({stmt, var});
            }
        }
        pkbWriter.setStatementModifiesRelationship(*stmtVarPairs);
    }

    void setProcedureModifiesRelationship(
        const std::unordered_map<std::string, std::unordered_set<std::string>>& procVarsMap) const {
        const auto procVarPairs = std::make_shared<std::unordered_set<std::pair<std::string, std::string>>>();
        for (const auto& procVars : procVarsMap) {
            auto proc = procVars.first;
            auto vars = procVars.second;
            for (const auto& var : vars) {
                procVarPairs->insert({proc, var});
            }
        }
        pkbWriter.setProcedureModifiesRelationship(*procVarPairs);
    }

    void setProcedureCallsRelationship(const std::shared_ptr<unordered_set<pair<string, string>>>& callsSet) const {
        pkbWriter.setCallsRelationships(*callsSet);
    }

    void setCfgBlock(const std::unordered_set<CFGBlock>& cfgBlock) {
        pkbWriter.setCfg(cfgBlock);
    }

protected:
    [[nodiscard]] PKB_STATEMENT createPKBStatment(NodeType stmtNodeType, int stmtNum) const {
        return {getPKBStmtType(stmtNodeType), stmtNum};
    }
    // only call with Statement NodeType
    [[nodiscard]] StatementType getPKBStmtType(NodeType stmtNodeType) const {
        switch (stmtNodeType) {
        case NodeType::READ:
            return StatementType::READ;
            break;
        case NodeType::PRINT:
            return StatementType::PRINT;
            break;
        case NodeType::ASSIGN:
            return StatementType::ASSIGN;
            break;
        case NodeType::CALL:
            return StatementType::CALL;
            break;
        case NodeType::WHILE_THEN:
            return StatementType::WHILE;
            break;
        case NodeType::IF_THEN_ELSE:
            return StatementType::IF;
            break;
        default:
            throw std::runtime_error("INVALID ARG to getPKBStmtType()");
        }
    }

private:
    const PKBWriter pkbWriter;
};
