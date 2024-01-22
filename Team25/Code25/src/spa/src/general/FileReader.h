#pragma once

#include <fstream>
#include <iostream>
#include <string>

class FileReader {
public:
    // Static method to read the file content and return it as a string
    static std::string ReadFile(const std::string& filename);
};
