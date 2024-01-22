#pragma once

#include "SP/AST/ASTNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/AST/WhileThenNode.h"
#include "SP/CfgModel/Cfg.h"
#include "SP/CfgModel/CfgNode.h"

class CfgExtractor {
public:
    CfgExtractor() = default;
    std::shared_ptr<Cfg> extractProgram(const std::shared_ptr<ProgramNode>& rootNode);

private:
    std::shared_ptr<CfgNode> extractStmtLst(const std::shared_ptr<StmtListNode>& stmtLstNode,
                                            const std::string& procName);
    void extractIf(const std::shared_ptr<IfThenElseNode>& ifNode, const std::string& procName);
    void extractWhile(const std::shared_ptr<WhileThenNode>& whileNode, const std::string& procName);

    std::shared_ptr<CfgNode> currCfgNode;
    int currNodeId = 1;
};
