#pragma once

#include <string>

#include "PKB/Interfaces/PKBWriter.h"
#include "SP/DesignExtraction/DesignExtractor.h"

class Orchestrator {
public:
    explicit Orchestrator(std::shared_ptr<PKBAdapter> pkbAdapter) : designExtractor({pkbAdapter}){};
    /**
     * Populates PKB with design abstractions based on input sourcefile
     * Tokenize -> Parse -> Validate Semantics -> Extract Design
     * @param sourceFile
     */
    void start(const std::string& sourceFile);

private:
    DesignExtractor designExtractor;
};
