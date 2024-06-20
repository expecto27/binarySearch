#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataStore.h"

namespace DataParser {
    template <VersionT T>
    void parse(std::vector<std::vector<std::string>>&& csvData, DataStore& data) {
        std::string carryKey = "";
        fmt::print("parse object {} size {}\n", T::name, csvData.size());
        for (auto&& instanceData : csvData) {
            std::shared_ptr<Object> instance = std::make_shared<Object>();
            instance->setKey(instanceData[3]);
            if (instance->getKey() != carryKey) {
                data.addObject(instance, T::name);
            }
            carryKey = instanceData[3];
            std::shared_ptr<T> version = std::make_shared<T>(std::move(instanceData));
            data.addVersion(version, instance->getKey(), T::name);
        }
    };
}
