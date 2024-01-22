#include "SP/Parser/Parser.h"

#include <unordered_map>

#include "ParserException.h"
#include "ProcedureParser.h"
#include "SP/AST/ProgramNode.h"
#include "StmtParser.h"

Parser::Parser(Tokenizer& tokenizer) : tokenizer(tokenizer) {
    StmtParser::resetStmtNum();
}
Parser::~Parser() = default;

ASTNodePtr Parser::parseProgram() {
    const std::string programName = "main";
    auto programNode = std::make_shared<ProgramNode>(programName);

    // parse the procedures within the program
    while (tokenizer.peekNextToken().getType() != EMPTY) {
        ASTNodePtr procNode = ProcedureParser::parseProcedure(tokenizer);
        programNode->addProcedure(procNode);

        Token closingBracketToken = tokenizer.getNextToken();
        if (closingBracketToken.getType() != RIGHT_CURLY) {
            throw ParserException("Missing curly bracket to end procedure: ");
        }
    }
    return programNode;
}
