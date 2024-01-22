#include "Orchestrator.h"

#include "SP/DesignExtraction/DesignExtractor.h"
#include "SP/Parser/Parser.h"
#include "SP/Parser/ParserException.h"
#include "SP/SemanticValidator/SemanticValidator.h"
#include "SP/Tokenizer/Tokenizer.h"

void Orchestrator::start(const std::string& sourceFile) {
    try {
        Tokenizer tokenizer{sourceFile};

        Parser parser{tokenizer};
        ASTNodePtr rootNode = parser.parseProgram();

        SemanticValidator semanticValidator{};
        semanticValidator.validate(rootNode);

        designExtractor.extractDesignAndPopulatePKB(rootNode);
    } catch (const ParserException& exception) {
        std::cout << "runtime error:" << exception.what() << std::endl;
        std::exit(1);
    }
}
