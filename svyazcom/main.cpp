#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include "DataStore.h"
#include "Models.h"
#include "CsvReader.h"
#include <chrono>
#include "DataParser.h"



int main(int argc, char* argv[])
{

    if (argc < 2)
        return 1;

    auto testData = CsvReader::readCsv(argv[1]);
    std::string key, fd;

    DataStore dataStore;

    auto imsiData = CsvReader::readCsv("imsi.csv");
    DataParser::parseImsi(imsiData, dataStore);

    auto pricesData = CsvReader::readCsv("prices.csv");
    DataParser::parsePrices(pricesData, dataStore);

    auto zonesData = CsvReader::readCsv("zones.csv");
    DataParser::parseZones(zonesData, dataStore);

    auto currencyRatesData = CsvReader::readCsv("currency_rates.csv");
    DataParser::parseCurrencyRates(currencyRatesData, dataStore);

    auto tcRelationTapData = CsvReader::readCsv("tc_relations_tap.csv");
    DataParser::parseTcRelationsTap(tcRelationTapData, dataStore);

    auto tcRelationCdrData = CsvReader::readCsv("tc_relations_cdr.csv");
    DataParser::parseTcRelationsCdr(tcRelationCdrData, dataStore);

    dataStore.murge();
    
    for (auto x : testData) {

        std::string objectType = x[0];

        std::string key = x[1];

        std::string fd = x[2];

        std::cout << "\n\ninput Data: Key: " << key << " fd: " << fd << " objectType:" << objectType;

        std::cout << "\nResult: " << dataStore.findVersion(key, fd, objectType) << "\n";

    }

    while (true) {

        std::string objectType;
        std::cout << "ObjectType: "; std::cin >> objectType;
        std::cout << "Key: "; std::cin >> key;

        int rid;

        std::cout << "Rid: "; std::cin >> rid;
        
        std::cout << "\nResult: " << dataStore.findVersion(key, rid, objectType) << "\n";

    }

    return 0;

}