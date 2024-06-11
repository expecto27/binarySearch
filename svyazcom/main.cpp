#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include "DataStore.h"
#include "Models.h"
#include "CsvReader.h"
#include <chrono>
#include <Windows.h>

std::string toString(std::shared_ptr<Version> ver, std::string key, std::string objectType, DataStore& data) {
    if (ver == nullptr) {
        return "null";
    }

    if (!(data.getIsCorrect(key, objectType))) {
        return "error";
    }
    return data.toString(key, objectType) + ver->toString();

}

int main()
{
    DataStore data;
    CsvReader::read(data);
    std::string key, fd;
    std::setlocale(LC_ALL, "en_US.UTF-8");
    SetConsoleOutputCP(CP_UTF8);

    

    std::vector<std::vector<std::string>> tests = CsvReader::readTests();
    for (auto x : tests) {

        std::string objectType = x[0];
        
        std::string key = x[1];
        
        std::string fd = x[2];
        
        std::cout << "\n\ninput Data: Key: " << key << " fd: " << fd << " objectType:" << objectType;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::cout << "\nResult: " << toString(data.findVersion(key, fd, objectType), key, objectType, data) << "\n";
        
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> duration = end - start;

        std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;
    }
    
    while (true) {

        std::string objectType;
        std::cout << "ObjectType: "; std::cin >> objectType;
        std::cout << "Key: "; std::cin >> key;
        
        std::string ridOrTd;
        
        std::cout << "Rid or Fd: "; std::cin >> ridOrTd;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::cout << "\nResult: " << toString(data.findVersion(key, ridOrTd, objectType), key, objectType, data) << "\n";
        
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> duration = end - start;

        std::cout << "Time taken by function: " << duration.count() << " seconds" << std::endl;

    }
}