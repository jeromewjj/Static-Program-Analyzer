#include "CfgExtractor.h"

#include "SP/AST/ProgramNode.h"
#include "SP/CfgModel//CfgConditionalNode.h"
#include "SP/CfgModel/Cfg.h"
#include "SP/CfgModel/CfgEndNode.h"
#include "SP/CfgModel/CfgNormalNode.h"

std::shared_ptr<Cfg> CfgExtractor::extractProgram(const std::shared_ptr<ProgramNode>& rootNode) {
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    vector<std::shared_ptr<ProcedureNode>> procedureNodes = rootNode->getProcedures();

    for (const auto& procNode : procedureNodes) {
        string procName = procNode->getName();
        std::shared_ptr<CfgNode> procCfgNode = extractStmtLst(procNode->getStmtList(), procName);
        cfg->addProcCfg(procCfgNode);
    }
    return cfg;
}

std::shared_ptr<CfgNode> CfgExtractor::extractStmtLst(const std::shared_ptr<StmtListNode>& stmtLstNode,
                                                      const std::string& procName) {
    std::vector<std::shared_ptr<StatementNode>> stmts = stmtLstNode->getSortedStmts();
    std::shared_ptr<CfgNode> headCfgNode;

    // Create appropriate head CfgModel node
    if (stmts[0]->getType() == NodeType::IF_THEN_ELSE or stmts[0]->getType() == NodeType::WHILE_THEN) {
        headCfgNode = std::make_shared<CfgConditionalNode>(currNodeId++, procName);
    }
    else {
        headCfgNode = std::make_shared<CfgNormalNode>(currNodeId++, procName);
    }

    // Set curr pointer to point to head
    currCfgNode = headCfgNode;

    for (const auto& stmt : stmts) {
        if (stmt->getType() == NodeType::IF_THEN_ELSE) {
            extractIf((const std::shared_ptr<IfThenElseNode>&)stmt, procName);
            continue;
        }
        else if (stmt->getType() == NodeType::WHILE_THEN) {
            extractWhile((const std::shared_ptr<WhileThenNode>&)stmt, procName);
            continue;
        }
        else if (currCfgNode->getType() == CfgNodeType::END) {
            std::shared_ptr<CfgNode> normalCfgNode = std::make_shared<CfgNormalNode>(currNodeId++, procName);
            currCfgNode->addChild(normalCfgNode);
            currCfgNode = normalCfgNode;
        }
        currCfgNode->addStmtNum(stmt->getStmtNum());
    }
    return headCfgNode;
}

void CfgExtractor::extractIf(const std::shared_ptr<IfThenElseNode>& ifNode, const std::string& procName) {
    std::shared_ptr<CfgNode> ifCfgNode;
    if (!currCfgNode->getStmts().empty() || currCfgNode->getType() == CfgNodeType::END) {
        ifCfgNode = std::make_shared<CfgConditionalNode>(currNodeId++, procName);
        currCfgNode->addChild(ifCfgNode);
        currCfgNode = ifCfgNode;
    }
    else {
        ifCfgNode = currCfgNode;
    }

    ifCfgNode->addStmtNum(ifNode->getStmtNum());
    std::shared_ptr<CfgNode> endCfgNode = std::make_shared<CfgEndNode>(currNodeId++, procName);

    // Create then cfg subtree
    std::shared_ptr<CfgNode> thenCfgNode = extractStmtLst(ifNode->getThenNode(), procName);
    ifCfgNode->addChild(thenCfgNode);

    // Connect last node in then subtree to end node
    currCfgNode->addChild(endCfgNode);

    // Create else cfg subtree
    std::shared_ptr<CfgNode> elseCfgNode = extractStmtLst(ifNode->getElseNode(), procName);
    ifCfgNode->addChild(elseCfgNode);

    // Connect last node in else subtree to end node
    currCfgNode->addChild(endCfgNode);

    currCfgNode = endCfgNode;
}

void CfgExtractor::extractWhile(const std::shared_ptr<WhileThenNode>& whileNode, const std::string& procName) {
    std::shared_ptr<CfgNode> whileCfgNode;
    if (!currCfgNode->getStmts().empty() || currCfgNode->getType() == CfgNodeType::END) {
        whileCfgNode = std::make_shared<CfgConditionalNode>(currNodeId++, procName);
        currCfgNode->addChild(whileCfgNode);
        currCfgNode = whileCfgNode;
    }
    else {
        whileCfgNode = currCfgNode;
    }

    whileCfgNode->addStmtNum(whileNode->getStmtNum());

    std::shared_ptr<CfgNode> thenCfgNode = extractStmtLst(whileNode->getThenNode(), procName);
    whileCfgNode->addChild(thenCfgNode);

    currCfgNode->addChild(whileCfgNode);

    std::shared_ptr<CfgNode> endCfgNode = std::make_shared<CfgEndNode>(currNodeId++, procName);
    whileCfgNode->addChild(endCfgNode);
    currCfgNode = endCfgNode;
}
