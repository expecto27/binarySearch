#include "DataStore.h"
#include "Models.h"
#include <algorithm>
#include <utility>

DataStore::DataStore() {}

void DataStore::addObject(std::shared_ptr<Object> obj, std::string objectType) {
    data[objectType][obj->getKey()] = obj;
}

void DataStore::addVersion(std::shared_ptr<Version> ver, std::string keyObject, std::string objectType) {
    data[objectType][keyObject]->addVersions(ver);
}

std::string DataStore::findVersion(const std::string& key, std::string timeStr, std::string objectType) {
    time_t time = static_cast<time_t>(std::stoull(timeStr));
    auto ver = data[objectType][key]->findVersion(time);

    if (ver == nullptr) {
        return "null";
    }
    if (!(data[objectType][key]->getIsCorrect())) {
        return "error";
    }
    return std::to_string(ver->getRid());
}

std::string DataStore::findVersion(const std::string& key, unsigned int rid, std::string objectType) {
    return data[objectType][key]->findVersionByRid(rid)->toString();
}
