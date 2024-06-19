#pragma once

#include "DataStore.h"
#include "Imsi.h"
#include "Prices.h"
#include "Zones.h"
#include "CurrencyRates.h"
#include "TcRelationsCdr.h"
#include "TcRelationTap.h"
#include <vector>
#include <string>
#include <memory>

class DataParser {
public:
    static void parseImsi(std::vector<std::vector<std::string>>&& csvData, DataStore& data);
    static void parsePrices(const std::vector<std::vector<std::string>>& csvData, DataStore& data);
    static void parseZones(const std::vector<std::vector<std::string>>& csvData, DataStore& data);
    static void parseCurrencyRates(const std::vector<std::vector<std::string>>& csvData, DataStore& data);
    static void parseTcRelationsCdr(const std::vector<std::vector<std::string>>& csvData, DataStore& data);
    static void parseTcRelationsTap(const std::vector<std::vector<std::string>>& csvData, DataStore& data);
};

