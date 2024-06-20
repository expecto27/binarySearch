#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "Models.h"

class DataStore {
    private:
        // entity -> key -> [version, ...]
        std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Object>>> data;

    public:
        DataStore();
        void addVersion(std::shared_ptr<Version> ver, std::string keyObject, std::string objectType);
        void addObject(std::shared_ptr<Object> obj, std::string objectType);

        bool getIsCorrect(std::string key, std::string objType) { return data[objType][key]->getIsCorrect(); }

        std::string toString(std::string key, std::string objType) { return data[objType][key]->toString(); }

        void murge() {
            for (const auto& outerPair : data) {
                const std::unordered_map<std::string, std::shared_ptr<Object>>& innerMap = outerPair.second;
                for (const auto& innerPair : innerMap) {
                    std::shared_ptr<Object> obj = innerPair.second;
                    obj->mergeData();
                }
            }
        }

        std::string findVersion(const std::string& key, std::string time, std::string objectType);
        std::string findVersion(const std::string& key, time_t time, std::string objectType);
        std::string findRid(const std::string& key, unsigned int rid, std::string objectType);
};
