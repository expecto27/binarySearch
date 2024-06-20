#include "Models.h"

#include <iostream>
#include <string>

#include "Imsi.h"

namespace svyazcom {
namespace clr {

std::string Object::toString() {
    std::string result = "";
    result += "Key: " + this->key;
    return result;
}

Version::version_ptr Object::binarySearch(const time_t time) {
    int left = 0;
    int right = versions.size() - 1;

    if (index_last_found != -1 && index_last_found >= left && index_last_found <= right) {
        const auto& version = versions[index_last_found];
        if (version->getFd() <= time && version->getTd() >= time) {
            return version;
        }
    }

    while (left <= right) {
        int         mid = left + (right - left) / 2;
        const auto& version = versions[mid];

        if (version->getFd() <= time && version->getTd() >= time) {
            index_last_found = mid;
            return version;
        }
        if (version->getFd() < time) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return nullptr;
}

void Object::mergeData() {
    for (int i = 0; i < versions.size() - 1; ++i) {
        if (versions[i]->getTd() > versions[i + 1]->getFd()) {
            this->setis_valid(false);
        }
    }
}

}} //namespace svyazcom::clr
