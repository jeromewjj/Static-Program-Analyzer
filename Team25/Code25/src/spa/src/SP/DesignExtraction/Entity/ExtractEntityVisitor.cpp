#include "ExtractEntityVisitor.h"

#include <iostream>

#include "SP/AST/AssignNode.h"
#include "SP/AST/CallNode.h"
#include "SP/AST/ConstantNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/ProcedureNode.h"
#include "SP/AST/VariableNode.h"
#include "SP/AST/WhileThenNode.h"
#include "SP/DesignExtraction/Relationship/Util/Helper.h"

using std::pair;
using std::unordered_set;
void ExtractEntityVisitor::extractEntity(const std::shared_ptr<const VariableNode>& node) const {
    std::string varName = node->getValue();
    this->addVar(varName);
}

void ExtractEntityVisitor::extractEntity(const std::shared_ptr<const ConstantNode>& node) const {
    std::string constVal = node->getValue();
    this->addConst(constVal);
}

void ExtractEntityVisitor::extractEntity(const std::shared_ptr<const ProcedureNode>& node) const {
    std::string procName = node->getName();
    this->addProcedure(procName);
}

void ExtractEntityVisitor::extractEntity(const std::shared_ptr<const CallNode>& node) const {
    const string procName = node->getProcedureName();
    const int stmtNum = node->getStmtNum();

    auto itr = procAndCallingStmts->find(procName);
    if (itr == procAndCallingStmts->end()) {
        (*procAndCallingStmts)[procName] = {stmtNum};
    }
    else {
        (*procAndCallingStmts)[procName].insert(stmtNum);
    }
}

void ExtractEntityVisitor::extractEntity(const std::shared_ptr<const AssignNode>& node) const {
    pair<string, std::shared_ptr<unordered_set<string>>> expressions = node->getParenthesizedExpression();
    this->addAssignInfo(node->getStmtNum(), node->getVarNode()->getName(), expressions.first, *expressions.second);
}

void ExtractEntityVisitor::extractEntity(const std::shared_ptr<const IfThenElseNode>& node) const {
    const int stmtNum = node->getStmtNum();
    const auto varNames = Helper::getVarNamesInSubtree(node->getConditionNode());
    if (!varNames.empty()) {
        ifConditionalVarsMap->insert({stmtNum, varNames});
    }
}

void ExtractEntityVisitor::extractEntity(const std::shared_ptr<const WhileThenNode>& node) const {
    const int stmtNum = node->getStmtNum();
    const auto varNames = Helper::getVarNamesInSubtree(node->getConditionNode());
    if (!varNames.empty()) {
        whileConditionalVarsMap->insert({stmtNum, varNames});
    }
}