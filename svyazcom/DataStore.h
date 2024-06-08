#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <map>
#include <any>
#include <string>
#include <algorithm>
#include "Models.h"



class DataStore {
private:

    std::unordered_map<std::string, std::shared_ptr<Object>> data;

public:
    DataStore();
    void merge();
    void addVersion(std::shared_ptr<Version> ver, std::string keyObject);
    void addObject(std::shared_ptr<Object> obj);
    std::string findVersion(const std::string& key, std::string time);
};
