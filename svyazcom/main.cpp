#include <iostream>
#include "DataStore.h"
#include "Models.h"
#include "CsvReader.h"
#include "DataParser.h"

#include <string>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

#include <time.h>

int main(int argc, char* argv[])
{

    if (argc < 2)
        return 1;

    auto testData = CsvReader::readCsv(argv[1]);

    DataStore dataStore;

    DataParser::parseImsi(CsvReader::readCsv("imsi.csv"), dataStore);
    DataParser::parsePrices(CsvReader::readCsv("prices.csv"), dataStore);
    DataParser::parseZones(CsvReader::readCsv("zones.csv"), dataStore);
    DataParser::parseCurrencyRates(CsvReader::readCsv("currency_rates.csv"), dataStore);
    DataParser::parseTcRelationsTap(CsvReader::readCsv("tc_relations_tap.csv"), dataStore);
    DataParser::parseTcRelationsCdr(CsvReader::readCsv("tc_relations_cdr.csv"), dataStore);

    dataStore.murge();
    int total{0};
    int failed{0};
    for (const auto &x : testData) {
        ++total;
        auto const &object   = x[0];
        auto const &key      = x[1];
        auto const &fd       = x[2];
        auto const &expected = x[3];
        auto const result = dataStore.findVersion(key, fd, object);
        if (result == expected) {
            fmt::print("{}:{} on {:%d.%m.%Y %H:%M:%S}: {} {}\n", 
                object, key, fmt::localtime(std::stol(fd)), result, fmt::styled("ok", fmt::fg(fmt::color::green))
            );
        }
        else {
            fmt::print("{}:{} on {:%d.%m.%Y %H:%M:%S}: {} {}, expected {}\n", 
                object, key, fmt::localtime(std::stol(fd)), result, fmt::styled("failed", fmt::fg(fmt::color::red)), expected
            );
            ++failed;
        }
    }
    if (failed) {
        fmt::print("{}/{} tests {}\n", failed, total, fmt::styled("failed", fmt::fg(fmt::color::red)));
    }
    else {
        fmt::print("{} all tests {}\n", total, fmt::styled("ok", fmt::fg(fmt::color::green)));
    }

    fmt::print("Performance test, wait ...\n");
    time_t s{1167609600};
    time_t e{1177609600};
    std::string key = "3.4";
    std::string object = "currency_rates";
    long int i{0};
    timespec from, till;
    clock_gettime(CLOCK_MONOTONIC, &from);
    while( s < e) {
        dataStore.findVersion(key, s, object);
        ++s;
        ++i;
    }
    clock_gettime(CLOCK_MONOTONIC, &till);
    float d = ((till.tv_sec - from.tv_sec) + (float)(till.tv_nsec - from.tv_nsec)/1e9);
    fmt::print("Performance done, times {} in {:.2}s rate {:.2}r/s \n", i, d, d/i);
    while (false) {
        std::string objectType;
        std::cout << "ObjectType: "; std::cin >> objectType;
        std::cout << "Key: "; std::cin >> key;
        int rid;
        std::cout << "Rid: "; std::cin >> rid;
        std::cout << "\nResult: " << dataStore.findVersion(key, rid, objectType) << "\n";
    }

    return 0;

}