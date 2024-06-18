#include <iostream>
#include "Models.h"
#include "Imsi.h"
#include <string>

std::string Object::toString() {
    std::string result = "";
    result += "Key: " + this->key;
    return result;
}

std::shared_ptr<Version> Object::binarySearch(const time_t time) {
    int left = 0;
    int right = versions.size() - 1;

    if (indexLastFound != -1 && indexLastFound >= left && indexLastFound <= right) {
        const auto& version = versions[indexLastFound];
        if (version->getFd() <= time && version->getTd() >= time) {
            return version;
        }
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;
        const auto& version = versions[mid];

        if (version->getFd() <= time && version->getTd() >= time) {
            indexLastFound = mid;
            return version;
        }
        if (version->getFd() < time) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return nullptr;
}

void Object::mergeData() {
    for (int i = 0; i < versions.size() - 1; ++i) {
        if (versions[i]->getTd() > versions[i + 1]->getFd()) {
            this->setIsCorrect(false);
        }
    }
}
