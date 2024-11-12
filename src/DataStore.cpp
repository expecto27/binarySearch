#include "DataStore.h"

#include <algorithm>
#include <utility>

#include "Models.h"

namespace svyazcom {
namespace clr {

DataStore::DataStore() {}

void DataStore::addObject(Object::object_ptr obj, std::string objectType) {
    data[objectType][obj->getKey()] = obj;
}

void DataStore::addVersion(Version::version_ptr ver, std::string keyObject, std::string objectType) {
    data[objectType][keyObject]->addVersions(ver);
}

std::string DataStore::VersionSearch(const std::string& object, const std::string& key, time_t time) {
    auto ver = data[object][key]->VersionFind(time);

    if (ver == nullptr) {
        return "null";
    }
    if (!(data[object][key]->getis_valid())) {
        return "error";
    }
    return std::to_string(ver->getRid());
}

std::string DataStore::findRid(const std::string& key, unsigned int rid, std::string objectType) {
    return data[objectType][key]->findVersionByRid(rid)->toString();
}

}} //namespace svyazcom::clr
