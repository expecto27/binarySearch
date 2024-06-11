#include <iostream>
#include "Models.h"
#include "CsvReader.h"
#include <vector>
#include "DataStore.h"
#include <sstream>
#include <fstream>
#include <string>
#include "Imsi.h"
#include "CurrencyRates.h"
#include "Prices.h"
#include "TcRelationsCdr.h"
#include "TcRelationTap.h"
#include "Zones.h"

std::vector<std::string> CsvReader::split(const std::string& str, char separator) {
    std::stringstream stream(str);
    std::vector<std::string> words;
    std::string word;
    while (std::getline(stream, word, separator)) {
        words.push_back(word);
    }
    return words;
}

std::string removeQuotes(std::string str) {
    std::string ans = "";
    for (char c : str) {
        if (c != '\"') {
            ans += c;
        }
    }
    return ans;
}


void CsvReader::readImsi(DataStore& data) {
        
        std::ifstream stream("imsi.csv");
        std::string title;
        std::string line;

        if (std::getline(stream, title)) { // читаем заголовок
            std::string carryKey = "";
            auto titleData = split(removeQuotes(title), ';');
            while (std::getline(stream, line)) {
                std::shared_ptr<Object> instance = std::make_shared<Object>();

                auto instanceData = split(removeQuotes(line), ';');

                instance->setKey(instanceData[3]);
                if (instance->getKey() != carryKey) {
                    data.addObject(instance, "imsi");
                }

                carryKey = instanceData.at(3);
                Imsi ver;
                std::shared_ptr<Imsi> imsiVer = std::make_shared<Imsi>();

                imsiVer->setRid(std::stoul(instanceData.at(0)));
                imsiVer->setFd(static_cast<time_t>(std::stoull(instanceData.at(1))));
                imsiVer->setTd(static_cast<time_t>(std::stoull(instanceData.at(2))));
                imsiVer->setS_imsi(instanceData.at(4));
                imsiVer->setE_imsi(instanceData.at(5));

                if (instanceData.at(6) != "")
                    imsiVer->setTap_code_id(std::stoul(instanceData.at(6)));

                if (instanceData.at(7) != "")
                    imsiVer->setFilial_id(std::stoul(instanceData.at(7)));
                
                if (instanceData.size() > 8 && instanceData.at(8) != "")
                    imsiVer->setImsi_region(std::stoul(instanceData.at(8)));

                data.addVersion(imsiVer, instance->getKey(), "imsi");
            }
        }
}

void CsvReader::readPrices(DataStore& data) {
    std::ifstream stream("prices.csv");
    std::string title;
    std::string line;

    if (std::getline(stream, title)) { // читаем заголовок
        std::string carryKey = "";
        auto titleData = split(removeQuotes(title), ';');
        while (std::getline(stream, line)) {
            std::shared_ptr<Object> instance = std::make_shared<Object>();

            auto instanceData = split(removeQuotes(line), ';');

            instance->setKey(instanceData[3]);
            if (instance->getKey() != carryKey) {
                data.addObject(instance, "prices");
            }
            carryKey = instanceData.at(3);
            Prices ver;
            std::shared_ptr<Prices> pricesVer = std::make_shared<Prices>();

            if (instanceData.at(0) != "")pricesVer->setRid(std::stoul(instanceData.at(0)));
            if (instanceData.at(1) != "")pricesVer->setFd(static_cast<time_t>(std::stoull(instanceData.at(1))));
            if (instanceData.at(2) != "")pricesVer->setTd(static_cast<time_t>(std::stoull(instanceData.at(2))));
            if (instanceData.at(4) != "")pricesVer->setId(std::stoul(instanceData.at(4)));
            if (instanceData.at(5) != "")pricesVer->setPlanId(std::stoul(instanceData.at(5)));
            if (instanceData.at(6) != "")pricesVer->setConnTypeId(std::stoul(instanceData.at(6)));
            if (instanceData.at(7) != "")pricesVer->setZoneName(instanceData.at(7));
            if (instanceData.at(8) != "")pricesVer->setIntervalGroupId(std::stoul(instanceData.at(8)));
            if (instanceData.at(9) != "")pricesVer->setTrangeGroupId(std::stoul(instanceData.at(9)));
            if (instanceData.at(10) != "")pricesVer->setTrangeId(std::stoul(instanceData.at(10)));
            if (instanceData.at(11) != "")pricesVer->setTrangeId(std::stoul(instanceData.at(11)));
            if (instanceData.at(12) != "")pricesVer->setCurrencyId(std::stoul(instanceData.at(12)));
            if (instanceData.at(13) != "")pricesVer->setCtl1(std::stoul(instanceData.at(13)));
            if (instanceData.at(14) != "")pricesVer->setCtl2(std::stoul(instanceData.at(14)));
            if (instanceData.at(15) != "")pricesVer->setCtl3(std::stoul(instanceData.at(15)));
            if (instanceData.at(16) != "") pricesVer->setServiceClass(instanceData.at(16));
            if (instanceData.at(17) != "") pricesVer->setPrice(std::stod(instanceData.at(17)));
            if (instanceData.at(18) != "")pricesVer->setCoef(std::stod(instanceData.at(18)));
            if (instanceData.at(19) != "") pricesVer->setFs(std::stoul(instanceData.at(19)));
            if (instanceData.at(20) != "")pricesVer->setCl(std::stoul(instanceData.at(20)));
            if (instanceData.at(21) != "")pricesVer->setRepriceMode(std::stoul(instanceData.at(21)));
            if (instanceData.size() > 22 && instanceData.at(22) != "")pricesVer->setP_fd(instanceData.at(22));

            data.addVersion(pricesVer, instance->getKey(), "prices");
        }
    }
}

void CsvReader::readZones(DataStore& data) {
    std::ifstream stream("zones.csv");
    std::string title;
    std::string line;

    if (std::getline(stream, title)) { // читаем заголовок
        std::string carryKey = "";
        auto titleData = split(removeQuotes(title), ';');
        while (std::getline(stream, line)) {
            std::shared_ptr<Object> instance = std::make_shared<Object>();

            auto instanceData = split(removeQuotes(line), ';');

            instance->setKey(instanceData[3]);
            if (instance->getKey() != carryKey) {
                data.addObject(instance, "zones");
            }

            carryKey = instanceData.at(0);
            std::shared_ptr<Zones> zonesVer = std::make_shared<Zones>();


            if (instanceData.at(0) != "") zonesVer->setRid(std::stoul(instanceData.at(0)));
            if (instanceData.at(1) != "") zonesVer->setFd(static_cast<time_t>(std::stoull(instanceData.at(1))));
            if (instanceData.at(2) != "") zonesVer->setTd(static_cast<time_t>(std::stoull(instanceData.at(2))));
            if (instanceData.at(4) != "") zonesVer->setId(std::stoul(instanceData.at(4)));
            if (instanceData.at(5) != "") zonesVer->setZoneName(instanceData.at(5));
            if (instanceData.at(6) != "") zonesVer->setDirectionName(instanceData.at(6));
            if (instanceData.at(7) != "") zonesVer->setDistributionName(instanceData.at(7));
            if (instanceData.at(8) != "") zonesVer->setOperatorId(std::stoul(instanceData.at(8)));
            if (instanceData.at(9) != "") zonesVer->setOperatorZoneId(std::stoul(instanceData.at(9)));
            if (instanceData.size() > 10 && instanceData.at(10) != "") zonesVer->setConnTypeId(std::stoul(instanceData.at(10)));

            data.addVersion(zonesVer, instance->getKey(), "zones");
        }
    }
}

void CsvReader::readCurrencyRates(DataStore& data) {
    std::ifstream stream("currency_rates.csv");
    std::string title;
    std::string line;

    if (std::getline(stream, title)) { // читаем заголовок
        std::string carryKey = "";
        auto titleData = split(removeQuotes(title), ';');
        while (std::getline(stream, line)) {
            std::shared_ptr<Object> instance = std::make_shared<Object>();

            auto instanceData = split(removeQuotes(line), ';');

            instance->setKey(instanceData[3]);
            if (instance->getKey() != carryKey) {
                data.addObject(instance, "currency_rates");
            }


            carryKey = instanceData.at(3);
            CurrencyRates ver;
            std::shared_ptr<CurrencyRates> currencyRatesVer = std::make_shared<CurrencyRates>();

            if (instanceData.at(0) != "") currencyRatesVer->setRid(std::stoul(instanceData.at(0)));
            if (instanceData.at(1) != "") currencyRatesVer->setFd(static_cast<time_t>(std::stoull(instanceData.at(1))));
            if (instanceData.at(2) != "") currencyRatesVer->setTd(static_cast<time_t>(std::stoull(instanceData.at(2))));
            if (instanceData.at(4) != "") currencyRatesVer->setFromId(std::stoul(instanceData.at(4)));
            if (instanceData.at(5) != "") currencyRatesVer->setToId(std::stoul(instanceData.at(5)));
            if (instanceData.size() > 6 && instanceData.at(6) != "") currencyRatesVer->setRate(std::stod(instanceData.at(6)));

            data.addVersion(currencyRatesVer, instance->getKey(), "currency_rates");
        }
    }
}

void CsvReader::readTcRelationTap(DataStore& data) {
    std::ifstream stream("tc_relations_tap.csv");
    std::string title;
    std::string line;

    if (std::getline(stream, title)) { // читаем заголовок
        std::string carryKey = "";
        auto titleData = split(removeQuotes(title), ';');
        while (std::getline(stream, line)) {
            std::shared_ptr<Object> instance = std::make_shared<Object>();

            auto instanceData = split(removeQuotes(line), ';');

            instance->setKey(instanceData[3]);
            if (instance->getKey() != carryKey) {
                data.addObject(instance, "tc_relations_tap");
            }


            carryKey = instanceData.at(3);
            std::shared_ptr<TcRelationTap> tcRelationTapVer = std::make_shared<TcRelationTap>();

            if (instanceData.at(0) != "") tcRelationTapVer->setRid(std::stoul(instanceData.at(0)));
            if (instanceData.at(1) != "") tcRelationTapVer->setFd(static_cast<time_t>(std::stoull(instanceData.at(1))));
            if (instanceData.at(2) != "") tcRelationTapVer->setTd(static_cast<time_t>(std::stoull(instanceData.at(2))));
            if (instanceData.at(4) != "") tcRelationTapVer->setTaxProfile(std::stoul(instanceData.at(4)));
            if (instanceData.at(5) != "") tcRelationTapVer->setServiceProfile(std::stoul(instanceData.at(5)));
            if (instanceData.at(6) != "") tcRelationTapVer->setTpCheck(std::stoul(instanceData.at(6)));
            if (instanceData.at(7) != "") tcRelationTapVer->setCheckMode(std::stoul(instanceData.at(7)));
            if (instanceData.at(8) != "") tcRelationTapVer->setTpReprice(std::stoul(instanceData.at(8)));
            if (instanceData.at(9) != "") tcRelationTapVer->setTransitTapMode(std::stoul(instanceData.at(9)));
            if (instanceData.at(10) != "") tcRelationTapVer->setTransitStart(instanceData.at(10));
            if (instanceData.at(11) != "") tcRelationTapVer->setTransitEnd(instanceData.at(11));
            if (instanceData.at(12) != "") tcRelationTapVer->setTransitPeriod(std::stoul(instanceData.at(12)));
            if (instanceData.at(13) != "") tcRelationTapVer->setGenRap(instanceData.at(13) == "1");
            if (instanceData.at(14) != "") tcRelationTapVer->setTransitRap(instanceData.at(14) == "1");
            if (instanceData.at(15) != "") tcRelationTapVer->setPassRcLessIc(instanceData.at(15) == "1");
            if (instanceData.at(16) != "") tcRelationTapVer->setIotThreshold(std::stoul(instanceData.at(16)));
            if (instanceData.size() > 17 && instanceData.at(17) != "") tcRelationTapVer->setIotDebug(std::stoul(instanceData.at(17)));

            data.addVersion(tcRelationTapVer, instance->getKey(), "tc_relations_tap");
        }
    }
}

std::vector < std::vector < std::string >> CsvReader::readTests() {
    std::ifstream stream("test.csv");
    std::string line;
    std::vector < std::vector < std::string >> res;
    if (std::getline(stream, line)) {
        while (std::getline(stream, line)) {
            auto instanceData = split(removeQuotes(line), ';');
            res.push_back(instanceData);
        }
    }
    return res;
}

void CsvReader::readTcRelationsCdr(DataStore& data) {
    std::ifstream stream("tc_relations_cdr.csv");
    std::string title;
    std::string line;

    if (std::getline(stream, title)) { // читаем заголовок
        std::string carryKey = "";
        auto titleData = split(removeQuotes(title), ';');
        while (std::getline(stream, line)) {

            std::shared_ptr<Object> instance = std::make_shared<Object>();
            
            auto instanceData = split(removeQuotes(line), ';');

            instance->setKey(instanceData[3]);
            if (instance->getKey() != carryKey) {
                data.addObject(instance, "tc_relations_cdr");
            }

            carryKey = instanceData.at(3);
            std::shared_ptr<TcRelationsCdr> tcRelationsCdrVer = std::make_shared<TcRelationsCdr>();

            if (instanceData.at(0) != "") tcRelationsCdrVer->setRid(std::stoul(instanceData.at(0)));
            if (instanceData.at(1) != "") tcRelationsCdrVer->setFd(static_cast<time_t>(std::stoull(instanceData.at(1))));
            if (instanceData.at(2) != "") tcRelationsCdrVer->setTd(static_cast<time_t>(std::stoull(instanceData.at(2))));
            if (instanceData.at(4) != "") tcRelationsCdrVer->setTpCdr(std::stoul(instanceData.at(4)));
            if (instanceData.at(5) != "") tcRelationsCdrVer->setTpCdr2(std::stoul(instanceData.at(5)));
            if (instanceData.at(6) != "") tcRelationsCdrVer->setGprsUnion(instanceData.at(6) == "1");
            if (instanceData.at(7) != "") tcRelationsCdrVer->setGenTapMode(std::stoul(instanceData.at(7)));
            if (instanceData.at(8) != "") tcRelationsCdrVer->setTransitStart(instanceData.at(8));
            if (instanceData.at(9) != "") tcRelationsCdrVer->setTransitEnd(instanceData.at(9));
            if (instanceData.at(10) != "") tcRelationsCdrVer->setTransitPeriod(std::stoul(instanceData.at(10)));
            if (instanceData.at(11) != "") tcRelationsCdrVer->setTapNotification(std::stoul(instanceData.at(11)));
            if (instanceData.at(12) != "") tcRelationsCdrVer->setTaskRid(std::stoul(instanceData.at(12)));
            if (instanceData.size() > 13 && instanceData.at(13) != "") tcRelationsCdrVer->setNumberTypes(instanceData.at(13));

            data.addVersion(tcRelationsCdrVer, instance->getKey(), "tc_relations_cdr");
        }
    }
}

void CsvReader::read(DataStore& data) {
    readImsi(data);
    readPrices(data);
    readCurrencyRates(data);
    readTcRelationsCdr(data);
    readTcRelationTap(data);
    readZones(data);
    data.murge();
}