#include "DataParser.h"
#include <memory>

void DataParser::parseImsi(std::vector<std::vector<std::string>>&& csvData, DataStore& data) {
    std::string carryKey = "";
    for (auto&& instanceData : csvData) {
        std::shared_ptr<Object> instance = std::make_shared<Object>();
        instance->setKey(instanceData[3]);
        if (instance->getKey() != carryKey) {
            data.addObject(instance, "imsi");
        }
        carryKey = instanceData[3];

        std::shared_ptr<Imsi> imsiVer = std::make_shared<Imsi>(std::move(instanceData));


        data.addVersion(imsiVer, instance->getKey(), "imsi");
    }
}

void DataParser::parsePrices(const std::vector<std::vector<std::string>>& csvData, DataStore& data) {
    std::string carryKey = "";
    for (const auto& instanceData : csvData) {
        std::shared_ptr<Object> instance = std::make_shared<Object>();
        instance->setKey(instanceData[3]);
        if (instance->getKey() != carryKey) {
            data.addObject(instance, "prices");
        }
        carryKey = instanceData[3];

        std::shared_ptr<Prices> pricesVer = std::make_shared<Prices>(instanceData);
        
        data.addVersion(pricesVer, instance->getKey(), "prices");
    }
}

void DataParser::parseZones(const std::vector<std::vector<std::string>>& csvData, DataStore& data) {
    std::string carryKey = "";
    for (const auto& instanceData : csvData) {
        std::shared_ptr<Object> instance = std::make_shared<Object>();
        instance->setKey(instanceData[3]);
        if (instance->getKey() != carryKey) {
            data.addObject(instance, "zones");
        }
        carryKey = instanceData[0];

        std::shared_ptr<Zones> zonesVer = std::make_shared<Zones>(instanceData);

        data.addVersion(zonesVer, instance->getKey(), "zones");
    }
}

void DataParser::parseCurrencyRates(const std::vector<std::vector<std::string>>& csvData, DataStore& data) {
    std::string carryKey = "";
    for (const auto& instanceData : csvData) {
        std::shared_ptr<Object> instance = std::make_shared<Object>();
        instance->setKey(instanceData[3]);
        if (instance->getKey() != carryKey) {
            data.addObject(instance, "currency_rates");
        }
        carryKey = instanceData[3];

        std::shared_ptr<CurrencyRates> currencyRatesVer = std::make_shared<CurrencyRates>(instanceData);
        

        data.addVersion(currencyRatesVer, instance->getKey(), "currency_rates");
    }
}

void DataParser::parseTcRelationsTap(const std::vector<std::vector<std::string>>& csvData, DataStore& data) {
    std::string carryKey = "";
    for (const auto& instanceData : csvData) {
        std::shared_ptr<Object> instance = std::make_shared<Object>();
        instance->setKey(instanceData[3]);
        if (instance->getKey() != carryKey) {
            data.addObject(instance, "tc_relations_tap");
        }
        carryKey = instanceData[3];
        
        std::shared_ptr<TcRelationTap> tcRelationTapVer = std::make_shared<TcRelationTap>();
        
        data.addVersion(tcRelationTapVer, instance->getKey(), "tc_relations_tap");

    }
}

void DataParser::parseTcRelationsCdr(const std::vector<std::vector<std::string>>& csvData, DataStore& data) {
    std::string carryKey = "";
    for (const auto& instanceData : csvData) {
        std::shared_ptr<Object> instance = std::make_shared<Object>();
        instance->setKey(instanceData[3]);
        if (instance->getKey() != carryKey) {
            data.addObject(instance, "tc_relations_cdr");
        }

        carryKey = instanceData[3];

        std::shared_ptr<TcRelationsCdr> tcRelationsCdrVer = std::make_shared<TcRelationsCdr>(instanceData);

        data.addVersion(tcRelationsCdrVer, instance->getKey(), "tc_relations_cdr");

    }
}
