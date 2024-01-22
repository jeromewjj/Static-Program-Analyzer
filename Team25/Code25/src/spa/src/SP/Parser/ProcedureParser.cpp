#include "ProcedureParser.h"

#include "SP/AST/ProcedureNode.h"
#include "SP/Parser/ParserException.h"
#include "StmtLstParser.h"

ProcedureParser::ProcedureParser() = default;

ASTNodePtr ProcedureParser::parseProcedure(Tokenizer& tokenizer) {
    string procedureName = getProcedureName(tokenizer);
    auto procedureNode = std::make_shared<ProcedureNode>(procedureName);
    procedureNode->setStmtList(StmtLstParser::parseStmtLst(tokenizer));

    return procedureNode;
}

string ProcedureParser::getProcedureName(Tokenizer& tokenizer) {
    Token procedureDeclaration = tokenizer.getNextToken();
    Token procedureName = tokenizer.getNextToken();
    Token procedureOpenBracket = tokenizer.getNextToken();

    // Check that first three tokens of a procedure are correct
    if (procedureDeclaration.getType() != ALPHANUM && procedureDeclaration.getValue() != "Procedure" &&
        procedureName.getType() != ALPHANUM && procedureOpenBracket.getType() != LEFT_CURLY) {
        throw ParserException("Invalid Procedure declaration");
    }
    return procedureName.getValue();
}
