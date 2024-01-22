#pragma once

#include <utility>

#include "FileReader.h"
#include "PKB/Interfaces/PKBReader.h"
#include "PKB/Interfaces/PKBWriter.h"
#include "PKB/PKB.h"
#include "QPS/QPS.h"
#include "SP/Orchestrator.h"

class SPA {
public:
    explicit SPA(PKB pkb) : pkbWriter(PKBWriter(pkb)), pkbReader(PKBReader(pkb)) {}

    inline void parse(std::string filename) const {
        std::string sourceCode = FileReader::ReadFile(filename);
        auto pkbAdapter = std::make_shared<PKBAdapter>(pkbWriter);
        auto sourceParser = Orchestrator(pkbAdapter);
        sourceParser.start(sourceCode);
    };

    inline std::vector<std::string> evaluate(std::string& query) {
        QPS qps = QPS(pkbReader);
        std::vector<std::string> result = qps.processQuery(query);
        pkbReader.clearCache();
        return result;
    }

private:
    PKBWriter pkbWriter;
    PKBReader pkbReader;
};
