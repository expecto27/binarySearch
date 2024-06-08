#pragma once

#include <iostream>
#include "Models.h"
#include <vector>
#include "DataStore.h"

class CsvReader {
private:
	static std::vector<std::string> split(const std::string& str, char separator);
	static void readImsi(DataStore& data);
	static void readPrices(DataStore& data);
	static void readCurrencyRates(DataStore& data);
	static void readZones(DataStore& data);
	static void readTcRelationsCdr(DataStore& data);
	static void readTcRelationTap(DataStore& data);
public:
	static void read(DataStore& data);
};