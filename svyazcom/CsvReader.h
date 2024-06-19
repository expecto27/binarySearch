#pragma once

#include <vector>
#include <string>
#include <algorithm>

class CsvReader {
public:
    static std::vector<std::vector<std::string>> readCsv(const std::string& filename);
private:
    static std::vector<std::string> split(const std::string& str, char separator);
    static std::string removeQuotes(const std::string& str);
};
