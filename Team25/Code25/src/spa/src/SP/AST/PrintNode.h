#pragma once
#include <cassert>

#include "StatementNode.h"
#include "VariableNode.h"

class PrintNode : public StatementNode {
public:
    PrintNode(const std::string& varName, int stmtNum) : StatementNode(NodeType::PRINT, "", stmtNum) {
        addChild(std::make_shared<VariableNode>(varName));
    }

    PrintNode(const std::shared_ptr<VariableNode>& varNode, int stmtNum) : StatementNode(NodeType::PRINT, "", stmtNum) {
        addChild(varNode);
    }

    std::shared_ptr<VariableNode> getVarNode() const {
        assert(children.size() == 1);
        return std::dynamic_pointer_cast<VariableNode>(children[0]);
    }
};