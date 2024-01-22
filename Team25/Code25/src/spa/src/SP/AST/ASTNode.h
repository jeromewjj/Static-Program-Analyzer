#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "NodeType.h"
#include "SP/DesignExtraction/Entity/ExtractCategoryVisitor.h"
#include "SP/DesignExtraction/Entity/ExtractEntityVisitor.h"

// Forward declaration of ASTNode for the ASTNodePtr typedef
class ASTNode;
using ASTNodePtr = std::shared_ptr<ASTNode>;
using ASTNodePtr_VIEWONLY = std::shared_ptr<const ASTNode>;

class VisitorInterface {
public:
    virtual void acceptVisitor(ExtractEntityVisitor& visitor) const = 0;
    virtual void acceptVisitor(ExtractCategoryVisitor& visitor) const = 0;
};
class ASTNode : public std::enable_shared_from_this<ASTNode>, public VisitorInterface {
public:
    ASTNode(NodeType type, std::string value = "") : type(type), value(std::move(value)) {}
    virtual ~ASTNode() = default;

    [[nodiscard]] NodeType getType() const {
        return type;
    }
    [[nodiscard]] std::string getValue() const {
        return value;
    }
    [[nodiscard]] const std::vector<std::shared_ptr<ASTNode>>& getChildren() const {
        return children;
    }
    virtual void addChild(const ASTNodePtr& child) {
        children.push_back(child);
    }

    friend bool operator==(const ASTNode& a, const ASTNode& b) {
        return a.type == b.type && a.value == b.value;
    };

    [[nodiscard]] std::vector<std::shared_ptr<const ASTNode>> breadthFirstTraversal() const;
    //    std::vector<std::shared_ptr<const ASTNode>> postorderTraversal() const;

    [[nodiscard]] virtual std::string toString() const {
        return "[" + value + ": " + nodeTypeToString(type) + "]";
    }

    // default does nothing
    // override in concreteASTNode classes to call visitor.extractEntity(...) logic
    //    void acceptVisitor(ExtractEntityVisitor& visitor) const {}
    //    void acceptVisitor(ExtractCategoricalEntityVisitor& visitor) const {}

private:
    NodeType type;
    std::string value;

protected:
    std::vector<ASTNodePtr> children;
};
