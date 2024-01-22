#include "FileReader.h"

std::string FileReader::ReadFile(const std::string& filename) {
    std::string sourceCode;
    std::ifstream file(filename);

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return "";
    }

    // Read the file line by line and append to the 'sourceCode' variable
    std::string line;
    while (std::getline(file, line)) {
        sourceCode += line + "\n"; // Add a newline character to separate lines
    }

    file.close();

    return sourceCode;
}