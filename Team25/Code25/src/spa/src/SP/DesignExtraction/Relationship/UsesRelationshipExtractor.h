#pragma once

#include <memory>

#include "RelationshipExtractor.h"
#include "SP/AST/AssignNode.h"
#include "SP/AST/CallNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/PrintNode.h"
#include "SP/AST/ProcedureNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/AST/WhileThenNode.h"

using std::pair;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class UsesRelationshipExtractor : public RelationshipExtractor {
public:
    explicit UsesRelationshipExtractor(std::shared_ptr<PKBAdapter> pkbAdapter)
        : pkbAdapter(pkbAdapter), usedVarsInStatement(unordered_map<int, unordered_set<string>>()),
          usedVarsInProcedure(unordered_map<string, unordered_set<string>>()) {}

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

    unordered_map<int, unordered_set<string>> getStmtToVarsMap() {
        return usedVarsInStatement;
    }
    unordered_map<string, unordered_set<string>> getProcToVarsMap() {
        return usedVarsInProcedure;
    }

private:
    const std::shared_ptr<PKBAdapter> pkbAdapter;

    void addUsedVars(int stmt, unordered_set<string> vars);
    void addUsedVars(const unordered_set<int>& stmts, unordered_set<string> vars);
    void addUsedVarsForProcedure(const string& procName, unordered_set<string> vars);
    void addUsedVarsForProcedure(const unordered_set<string>& procNames, unordered_set<string> vars);

    // maps statement -> usedVars
    unordered_map<int, unordered_set<string>> usedVarsInStatement;
    // maps proc -> usedVars
    unordered_map<string, unordered_set<string>> usedVarsInProcedure;
};

namespace Used {
    unordered_set<string> varNames(std::shared_ptr<const StmtListNode> stmtListNode);
    unordered_set<string> varNames(const std::shared_ptr<const AssignNode>& assignNode);
    unordered_set<string> varNames(const std::shared_ptr<const PrintNode>& printNode);
    unordered_set<string> varNames(std::shared_ptr<const IfThenElseNode> ifNode);
    unordered_set<string> varNames(std::shared_ptr<const WhileThenNode> whileNode);
}
