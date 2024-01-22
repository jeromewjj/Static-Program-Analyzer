#pragma once

#include <memory>
#include <utility>

#include "RelationshipExtractor.h"
#include "SP/AST/AssignNode.h"
#include "SP/AST/CallNode.h"
#include "SP/AST/IfThenElseNode.h"
#include "SP/AST/PrintNode.h"
#include "SP/AST/ProcedureNode.h"
#include "SP/AST/ProgramNode.h"
#include "SP/AST/WhileThenNode.h"

using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class CallsRelationshipExtractor : public RelationshipExtractor {
public:
    explicit CallsRelationshipExtractor(std::shared_ptr<PKBAdapter> pkbAdapter)
        : pkbAdapter(std::move(pkbAdapter)), callsSet(std::make_shared<unordered_set<pair<string, string>>>()) {}

    void extractRelationshipAndFlush(const ASTNodePtr& rootNode) override {
        extractRelationship(rootNode);
        flush();
    };

    [[nodiscard]] auto getCallsSet() const {
        return callsSet;
    }

    void extractRelationship(const ASTNodePtr& rootNode) override;
    void flush() override;

private:
    const std::shared_ptr<PKBAdapter> pkbAdapter;

    // set of pairs of proc1, proc2 (where proc1 called proc2)
    std::shared_ptr<unordered_set<pair<string, string>>> callsSet;
};
