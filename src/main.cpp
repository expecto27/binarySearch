#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <time.h>

#include <iostream>
#include <string>

#include "CsvReader.h"
#include "DataParser.h"
#include "data_store.h"
#include "Models.h"

void usage() {
    fmt::print("usage: version-search test.csv\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        return 1;
    }

    auto test_data = csvreader::CsvReader::ReadFile(argv[1]);

    data_store data_store

    DataParser::ParseRows<Imsi>(csvreader::CsvReader::ReadFile("imsi.csv"), data_store);
    DataParser::ParseRows<Prices>(csvreader::CsvReader::ReadFile("prices.csv"), data_store);
    DataParser::ParseRows<Zones>(csvreader::CsvReader::ReadFile("zones.csv"), data_store);
    DataParser::ParseRows<CurrencyRates>(csvreader::CsvReader::ReadFile("currency_rates.csv"), data_store);
    DataParser::ParseRows<TcRelationTap>(csvreader::CsvReader::ReadFile("tc_relations_tap.csv"), data_store);
    DataParser::ParseRows<TcRelationsCdr>(csvreader::CsvReader::ReadFile("tc_relations_cdr.csv"), data_store);

    data_store.murge(); //what is for

    int total{0};
    int failed{0};
    for (const auto &x : test_data) {
        ++total;
        auto const &object   = x[0];
        auto const &key      = x[1];
        auto const &fd       = static_cast<time_t>(std::stoull(x[2]));
        auto const &expected = x[3];
        auto const result = data_store.findVersion(key, fd, object);
        if (result == expected) {
            fmt::print(
                "{}:{} on {:%d.%m.%Y %H:%M:%S}: {} {}\n", object, key, fmt::localtime(std::stol(fd)), result,
                fmt::styled("ok", fmt::fg(fmt::color::green))
            );
        } else {
            fmt::print(
                "{}:{} on {:%d.%m.%Y %H:%M:%S}: {} {}, expected {}\n", object, key, fmt::localtime(std::stol(fd)),
                result, fmt::styled("failed", fmt::fg(fmt::color::red)), expected
            );
            ++failed;
        }
    }
    if (failed) {
        fmt::print("{}/{} tests {}\n", failed, total, fmt::styled("failed", fmt::fg(fmt::color::red)));
    } else {
        fmt::print("{} all tests {}\n", total, fmt::styled("ok", fmt::fg(fmt::color::green)));
    }

    fmt::print("Performance test, wait ...\n");
    time_t      s{1167609600};
    time_t      e{1177609600};
    std::string key = "3.4";
    std::string object = "currency_rates";
    long int    i{0};
    timespec    from, till;
    clock_gettime(CLOCK_MONOTONIC, &from);
    while (s < e) {
        data_store.findVersion(key, s, object);
        ++s;
        ++i;
    }
    clock_gettime(CLOCK_MONOTONIC, &till);
    float d = ((till.tv_sec - from.tv_sec) + (float)(till.tv_nsec - from.tv_nsec) / 1e9);
    fmt::print("Performance done, times {} in {:.2}s rate {:.2}r/s \n", i, d, d / i);

    return 0;
}
