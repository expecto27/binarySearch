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
        typedef std::unordered_map<key_t, Object *> objects_t;
        typedef std::unordered_map<key_t, instances_t> entities_t;

    private:
        entities_t data;

    public:
        DataStore();
        void VersionAdd(const key_t &object, const key_t &key, const Version *version);
        void ObjectAdd(const key_t &object, Object *entity);

        const Version *VersionSearch(const key_t& object, const key_t& key, const time_t time);
};

}} //namespace svyazcom::clr
