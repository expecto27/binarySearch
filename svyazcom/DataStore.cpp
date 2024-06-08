#include "DataStore.h"
#include "Models.h"
#include <algorithm>
#include <utility>

DataStore::DataStore() {}

void DataStore::addObject(std::shared_ptr<Object> obj) {
    data[obj->getKey()] = obj;
}

void DataStore::merge() {
    for (auto it = data.begin(); it != data.end(); ++it) {
        it->second->mergeData();
    }
}
void DataStore::addVersion(std::shared_ptr<Version> ver, std::string keyObject) {
    data[keyObject]->addVersions(ver);
}

std::string DataStore::findVersion(const std::string& key, std::string timeStr) {
    if (data[key] == nullptr) {
        return "null";
    }
    if (!data[key]->getIsCorrect()) {
        return "Некорректный объект " + data[key]->toString();
    }
    time_t time = static_cast<time_t>(std::stoull(timeStr));
    std::shared_ptr<Version> ver = data[key]->findVersion(time);
    if (ver == nullptr) return "null";
    return data[key]->toString() + ver->toString();
}
