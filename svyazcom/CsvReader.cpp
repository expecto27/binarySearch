#include "CsvReader.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

std::vector<std::string> CsvReader::split(const std::string& str, char separator) {
    std::stringstream stream(str);
    std::vector<std::string> words;
    std::string word;
    while (std::getline(stream, word, separator)) {
        words.push_back(word);
    }
    return words;
}

std::string CsvReader::removeQuotes(const std::string& str) {
    std::string result;
    std::copy_if(str.begin(), str.end(), std::back_inserter(result), [](const auto &c){return c != '\"';});
    return result;
}

std::vector<std::vector<std::string>> CsvReader::readCsv(const std::string& filename) {

    std::ifstream stream(filename);
    std::string line;
    std::vector<std::vector<std::string>> data;

    if (std::getline(stream, line)) {
        
        while (std::getline(stream, line)) {
           
            auto row = split(removeQuotes(line), ';');
            data.push_back(row);
        }
    }
    return data;
}
