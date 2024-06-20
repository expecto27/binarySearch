#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CurrencyRates.h"
#include "DataStore.h"
#include "Imsi.h"
#include "Prices.h"
#include "TcRelationTap.h"
#include "TcRelationsCdr.h"
#include "Zones.h"

namespace DataParser {
    template <VersionT T>
    void parse(const std::vector<std::vector<std::string>>& csvData, DataStore& data) {
        std::string carryKey = "";
        for (const auto& instanceData : csvData) {
            std::shared_ptr<Object> instance = std::make_shared<Object>();
            instance->setKey(instanceData[3]);
            if (instance->getKey() != carryKey) {
                data.addObject(instance, T::name);
            }
            carryKey = instanceData[3];
            std::shared_ptr<T> version = std::make_shared<T>();
            data.addVersion(version, instance->getKey(), T::name);
        }
    };
}
