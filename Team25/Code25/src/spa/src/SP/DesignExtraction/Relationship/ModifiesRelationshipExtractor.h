#pragma once

#include <memory>

#include "RelationshipExtractor.h"
#include "SP/AST/AssignNode.h"
#include "SP/AST/CallNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/ProcedureNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/AST/ReadNode.h"
#include "SP/AST/WhileThenNode.h"

using std::pair;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class ModifiesRelationshipExtractor : public RelationshipExtractor {
public:
    explicit ModifiesRelationshipExtractor(std::shared_ptr<PKBAdapter> pkbAdapter)
        : pkbAdapter(pkbAdapter), modifiedVarsInStatement(unordered_map<int, unordered_set<string>>()),
          modifiedVarsInProcedure(unordered_map<string, unordered_set<string>>()) {}

    void extractRelationshipAndFlush(const ASTNodePtr& rootNode) override {
        extractRelationship(rootNode);
        flush();
    };

    void extractRelationship(const ASTNodePtr& rootNode) override;
    static unordered_map<string, unordered_set<string>>
    getProceduresCallingProcedure(const std::shared_ptr<ProgramNode>& programNode);
    void processProcedure(const std::shared_ptr<ProcedureNode>& procedureNode,
                          const unordered_set<int>& stmtSubscribersOfProcedure,
                          const unordered_set<string>& procedureSubscribersOfProcedure);
    void processStmtList(const std::shared_ptr<StmtListNode>& stmtListNode,
                         const unordered_set<int>& stmtSubscribersOfStmtList,
                         const unordered_set<string>& procedureSubscribersOfStmtList);
    void flush() override;

    std::unordered_map<int, unordered_set<string>> getStmtToVarsMap() {
        return modifiedVarsInStatement;
    }
    std::unordered_map<string, unordered_set<string>> getProcToVarsMap() {
        return modifiedVarsInProcedure;
    }

private:
    const std::shared_ptr<PKBAdapter> pkbAdapter;

    void addModifiedVars(int stmt, unordered_set<string> vars);
    void addModifiedVars(const unordered_set<int>& stmts, unordered_set<string> vars);
    void addModifiedVarsForProcedure(const string& procName, unordered_set<string> vars);
    void addModifiedVarsForProcedure(const unordered_set<string>& procNames, unordered_set<string> vars);

    // maps statement -> usedVars
    std::unordered_map<int, unordered_set<string>> modifiedVarsInStatement;
    // maps proc -> usedVars
    std::unordered_map<string, unordered_set<string>> modifiedVarsInProcedure;
};

namespace Modified {
    std::unordered_set<string> varNames(std::shared_ptr<const StmtListNode> stmtListNode);
    std::unordered_set<string> varNames(const std::shared_ptr<const AssignNode>& assignNode);
    std::unordered_set<string> varNames(const std::shared_ptr<const ReadNode>& printNode);
    std::unordered_set<string> varNames(std::shared_ptr<const IfThenElseNode> ifNode);
    std::unordered_set<string> varNames(std::shared_ptr<const WhileThenNode> whileNode);
}