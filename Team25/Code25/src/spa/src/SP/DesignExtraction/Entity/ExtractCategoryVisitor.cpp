#include "ExtractCategoryVisitor.h"

#include "SP/AST/StatementNode.h"

void ExtractCategoryVisitor::extractEntity(const std::shared_ptr<const StatementNode>& node) const {
    this->addStmt(node->getType(), node->getStmtNum());
}