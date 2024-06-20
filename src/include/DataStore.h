#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "Models.h"
#include "CurrencyRates.h"
#include "Imsi.h"
#include "Prices.h"
#include "TcRelationTap.h"
#include "TcRelationsCdr.h"
#include "Zones.h"

namespace svyazcom {
namespace clr {

class DataStore {
    public:
        typedef std::string key_t;
        typedef std::unordered_map<key_t, Object::object_ptr>> instances_t;
        typedef std::unordered_map<key_t, instances_t> entities_t;

    private:
        entities_t data;

    public:
        DataStore();
        void addVersion(Version::version_ptr ver, std::string keyObject, std::string objectType);
        void addObject(Object::object_ptr obj, std::string objectType);

        bool getis_valid(std::string key, std::string objType) { return data[objType][key]->getis_valid(); }

        std::string toString(std::string key, std::string objType) { return data[objType][key]->toString(); }

        void murge() {
            for (const auto& outerPair : data) {
                const std::unordered_map<std::string, Object::object_ptr>& innerMap = outerPair.second;
                for (const auto& innerPair : innerMap) {
                    Object::object_ptr obj = innerPair.second;
                    obj->mergeData();
                }
            }
        }

        std::string VersionSearch(const std::string& object, const std::string& key, const time_t time);
};

}} //namespace svyazcom::clr
