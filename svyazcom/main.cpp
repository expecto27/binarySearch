#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <variant>
#include <any>
#include "DataStore.h"
#include "Models.h"
#include "CsvReader.h"


int main()
{
    DataStore data;
    CsvReader::read(data);
    std::string key, fd;
    std::setlocale(LC_ALL, "");
    while (true) {
        std::cout << "Key: "; std::cin >> key;
        std::cout << "Time: "; std::cin >> fd;
        std::cout << "\nResult:\n" << data.findVersion(key, fd) << "\n\n";
    }
}