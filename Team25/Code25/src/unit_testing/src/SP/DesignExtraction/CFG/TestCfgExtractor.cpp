#include "../../AST/MockASTs.h"
#include "SP/CfgModel/Cfg.h"
#include "SP/DesignExtraction/CFG/CfgExtractor.h"
#include "SP/Parser/Parser.h"
#include "SP/Parser/ParserException.h"
#include "catch.hpp"

TEST_CASE("Build Basic CFG - mock1", "[Basic CfgModel builder]") {
    auto rootNode = MockASTs::mock1();
    CfgExtractor cfgExtractor{};
    std::shared_ptr<Cfg> cfgManager = cfgExtractor.extractProgram(rootNode);
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> cfgs = cfgManager->bfsAllProcs();

    string node1 = "Node ID: 1, ProcName: p, Type: Normal, Stmt Numbers: (3,2,1,) Children: ()";

    std::vector<std::vector<std::string>> correctNodeStrings = {{node1}};

    REQUIRE(correctNodeStrings.size() == cfgs.size());
    for (size_t i = 0; i < correctNodeStrings.size(); ++i) {
        const std::vector<std::string>& nodeStringVector = correctNodeStrings[i];
        const std::vector<std::shared_ptr<const CfgNode>>& cfg = cfgs[i];
        REQUIRE(nodeStringVector.size() == cfg.size());

        for (size_t j = 0; j < nodeStringVector.size(); ++j) {
            const std::string& nodeString = nodeStringVector[j];
            const std::shared_ptr<const CfgNode>& cfgNode = cfg[j];
            REQUIRE(nodeString == cfgNode->toString());
        }
    }
}

TEST_CASE("Build CFG with if and while", "[Basic CfgModel builder]") {
    auto rootNode = MockASTs::mock2();
    CfgExtractor cfgExtractor{};
    std::shared_ptr<Cfg> cfgManager = cfgExtractor.extractProgram(rootNode);
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> cfgs = cfgManager->bfsAllProcs();

    string node1 = "Node ID: 1, ProcName: p, Type: Normal, Stmt Numbers: (1,) Children: (2,)";
    string node2 = "Node ID: 2, ProcName: p, Type: Conditional, Stmt Numbers: (2,) Children: (4,3,)";
    string node3 = "Node ID: 3, ProcName: p, Type: Normal, Stmt Numbers: (3,) Children: (2,)";
    string node4 = "Node ID: 4, ProcName: p, Type: End, Stmt Numbers: () Children: (5,)";
    string node5 = "Node ID: 5, ProcName: p, Type: Normal, Stmt Numbers: (4,) Children: (6,)";
    string node6 = "Node ID: 6, ProcName: p, Type: Conditional, Stmt Numbers: (5,) Children: (9,8,)";
    string node8 = "Node ID: 8, ProcName: p, Type: Normal, Stmt Numbers: (6,) Children: (7,)";
    string node9 = "Node ID: 9, ProcName: p, Type: Normal, Stmt Numbers: (7,) Children: (7,)";
    string node7 = "Node ID: 7, ProcName: p, Type: End, Stmt Numbers: () Children: ()";

    std::vector<std::vector<std::string>> correctNodeStrings = {
        {node1, node2, node3, node4, node5, node6, node8, node9, node7}};

    REQUIRE(correctNodeStrings.size() == cfgs.size());
    for (size_t i = 0; i < cfgs.size(); ++i) {
        const std::vector<std::string>& nodeStringVector = correctNodeStrings[i];
        const std::vector<std::shared_ptr<const CfgNode>>& cfg = cfgs[i];
        REQUIRE(nodeStringVector.size() == cfg.size());

        for (size_t j = 0; j < cfg.size(); ++j) {
            const std::string& nodeString = nodeStringVector[j];
            const std::shared_ptr<const CfgNode>& cfgNode = cfg[j];
            REQUIRE(nodeString == cfgNode->toString());
        }
    }
}

TEST_CASE("Build CFG multiple statements", "[Basic CfgModel builder]") {
    auto rootNode = MockASTs::mock3();
    CfgExtractor cfgExtractor{};
    std::shared_ptr<Cfg> cfgManager = cfgExtractor.extractProgram(rootNode);
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> cfgs = cfgManager->bfsAllProcs();

    string node1 = "Node ID: 1, ProcName: p1, Type: Normal, Stmt Numbers: (5,4,3,2,1,) Children: ()";
    string node2 = "Node ID: 2, ProcName: p2, Type: Normal, Stmt Numbers: (6,) Children: ()";
    string node3 = "Node ID: 3, ProcName: p3, Type: Normal, Stmt Numbers: (7,) Children: ()";

    std::vector<std::vector<std::string>> correctNodeStrings = {{node1}, {node2}, {node3}};

    REQUIRE(correctNodeStrings.size() == cfgs.size());
    for (size_t i = 0; i < correctNodeStrings.size(); ++i) {
        const std::vector<std::string>& nodeStringVector = correctNodeStrings[i];
        const std::vector<std::shared_ptr<const CfgNode>>& cfg = cfgs[i];
        REQUIRE(nodeStringVector.size() == cfg.size());

        for (size_t j = 0; j < nodeStringVector.size(); ++j) {
            const std::string& nodeString = nodeStringVector[j];
            const std::shared_ptr<const CfgNode>& cfgNode = cfg[j];
            REQUIRE(nodeString == cfgNode->toString());
        }
    }
}

TEST_CASE("if in while test", "[Basic CfgModel builder]") {
    std::string input = R"(
            Procedure p {
               read x;
               while (x < 0) {
                 if (y < 0) then {
                    print y;
                    } else {
                    print x;
                    }
                }
               read y;
             }
        )";

    Tokenizer tokenizer = Tokenizer(input);
    Parser parser = Parser(tokenizer);
    ASTNodePtr rootNode = parser.parseProgram();

    CfgExtractor cfgExtractor{};
    std::shared_ptr<Cfg> cfgManager = cfgExtractor.extractProgram((const shared_ptr<ProgramNode>&)rootNode);
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> cfgs = cfgManager->bfsAllProcs();

    string node1 = "Node ID: 1, ProcName: p, Type: Normal, Stmt Numbers: (1,) Children: (2,)";
    string node2 = "Node ID: 2, ProcName: p, Type: Conditional, Stmt Numbers: (2,) Children: (7,3,)";
    string node3 = "Node ID: 3, ProcName: p, Type: Conditional, Stmt Numbers: (3,) Children: (6,5,)";
    string node4 = "Node ID: 7, ProcName: p, Type: End, Stmt Numbers: () Children: (8,)";
    string node5 = "Node ID: 5, ProcName: p, Type: Normal, Stmt Numbers: (4,) Children: (4,)";
    string node6 = "Node ID: 6, ProcName: p, Type: Normal, Stmt Numbers: (5,) Children: (4,)";
    string node7 = "Node ID: 8, ProcName: p, Type: Normal, Stmt Numbers: (6,) Children: ()";
    string node8 = "Node ID: 4, ProcName: p, Type: End, Stmt Numbers: () Children: (2,)";

    std::vector<std::vector<std::string>> correctNodeStrings = {
        {node1, node2, node3, node4, node5, node6, node7, node8}};

    REQUIRE(correctNodeStrings.size() == cfgs.size());
    for (size_t i = 0; i < cfgs.size(); ++i) {
        const std::vector<std::string>& nodeStringVector = correctNodeStrings[i];
        const std::vector<std::shared_ptr<const CfgNode>>& cfg = cfgs[i];
        REQUIRE(nodeStringVector.size() == cfg.size());

        for (size_t j = 0; j < cfg.size(); ++j) {
            const std::string& nodeString = nodeStringVector[j];
            const std::shared_ptr<const CfgNode>& cfgNode = cfg[j];
            REQUIRE(nodeString == cfgNode->toString());
        }
    }
}

TEST_CASE("while in if test", "[Basic CfgModel builder]") {
    std::string input = R"(
            Procedure p {
                if (y < 0) then {
                    while(x<0){call y;}
                } else {
                    while(x<0){x = 2;}
                }
             }
        )";

    Tokenizer tokenizer = Tokenizer(input);
    Parser parser = Parser(tokenizer);
    ASTNodePtr rootNode = parser.parseProgram();

    CfgExtractor cfgExtractor{};
    std::shared_ptr<Cfg> cfgManager = cfgExtractor.extractProgram((const shared_ptr<ProgramNode>&)rootNode);
    std::vector<std::vector<std::shared_ptr<const CfgNode>>> cfgs = cfgManager->bfsAllProcs();

    string node1 = "Node ID: 1, ProcName: p, Type: Conditional, Stmt Numbers: (1,) Children: (6,3,)";
    string node2 = "Node ID: 3, ProcName: p, Type: Conditional, Stmt Numbers: (2,) Children: (5,4,)";
    string node3 = "Node ID: 6, ProcName: p, Type: Conditional, Stmt Numbers: (4,) Children: (8,7,)";
    string node4 = "Node ID: 4, ProcName: p, Type: Normal, Stmt Numbers: (3,) Children: (3,)";
    string node5 = "Node ID: 5, ProcName: p, Type: End, Stmt Numbers: () Children: (2,)";
    string node6 = "Node ID: 7, ProcName: p, Type: Normal, Stmt Numbers: (5,) Children: (6,)";
    string node7 = "Node ID: 8, ProcName: p, Type: End, Stmt Numbers: () Children: (2,)";
    string node8 = "Node ID: 2, ProcName: p, Type: End, Stmt Numbers: () Children: ()";

    std::vector<std::vector<std::string>> correctNodeStrings = {
        {node1, node2, node3, node4, node5, node6, node7, node8}};

    REQUIRE(correctNodeStrings.size() == cfgs.size());
    for (size_t i = 0; i < cfgs.size(); ++i) {
        const std::vector<std::string>& nodeStringVector = correctNodeStrings[i];
        const std::vector<std::shared_ptr<const CfgNode>>& cfg = cfgs[i];
        REQUIRE(nodeStringVector.size() == cfg.size());

        for (size_t j = 0; j < cfg.size(); ++j) {
            const std::string& nodeString = nodeStringVector[j];
            const std::shared_ptr<const CfgNode>& cfgNode = cfg[j];
            std::cout << cfgNode->toString() << std::endl;

            REQUIRE(nodeString == cfgNode->toString());
        }
    }
}