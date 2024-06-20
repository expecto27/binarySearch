#include "CsvReader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace csvreader {

row_t CsvReader::SplitRaw(const std::string& raw, char separator) {
    std::stringstream stream(raw);
    field_t           word;
    row_t             words;

    while (std::getline(stream, word, separator)) {
        words.push_back(word);
    }
    return words;
}

field_t CsvReader::RemoveQuotes(const field_t& field) {
    field_t data;
    std::copy_if(field.begin(), field.end(), std::back_inserter(data), [](const auto& c) { return c != '\"'; });
    return data;
}

rows_t CsvReader::ReadFile(const std::string& filename) {
    std::ifstream stream(filename);
    std::string   line;
    rows_t rows;

    if (std::getline(stream, line)) {
        while (std::getline(stream, line)) {
            auto row = SplitRaw(RemoveQuotes(line), ';');
            rows.push_back(row);
        }
    }
    return rows;
}

} //namespace csvreader
