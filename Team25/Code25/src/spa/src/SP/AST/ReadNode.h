#pragma once
#include <cassert>

#include "StatementNode.h"
#include "VariableNode.h"

class ReadNode : public StatementNode {
public:
    ReadNode(const std::string& varName, int stmtNum) : StatementNode(NodeType::READ, "", stmtNum) {
        addChild(std::make_shared<VariableNode>(varName));
    }

    ReadNode(const std::shared_ptr<VariableNode>& varNode, int stmtNum) : StatementNode(NodeType::READ, "", stmtNum) {
        addChild(varNode);
    }

    std::shared_ptr<VariableNode> getVarNode() const {
        assert(children.size() == 1);
        return std::static_pointer_cast<VariableNode>(children[0]);
    }
};
