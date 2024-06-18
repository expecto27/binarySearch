#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include "Models.h"



class DataStore {
private:

    std::unordered_map <
        std::string, std::unordered_map < std::string, std::shared_ptr<Object> >
    > data;

public:
    DataStore();
    void addVersion(std::shared_ptr<Version> ver, std::string keyObject, std::string objectType);
    void addObject(std::shared_ptr<Object> obj, std::string objectType);

    bool getIsCorrect(std::string key, std::string objType) {
        return data[objType][key]->getIsCorrect();
    }

    std::string toString(std::string key, std::string objType) {
        return data[objType][key]->toString();
    }

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
    std::string findVersion(const std::string& key, unsigned int rid, std::string objectType);
};
