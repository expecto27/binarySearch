#include "Models.h"

#include <iostream>
#include <string>

#include "Imsi.h"

namespace svyazcom {
namespace clr {

const Version *Object::Search(const time_t time) {

    int left = 0;
    int right = versions.size() - 1;

    if (index_last_found != -1 && index_last_found >= left && index_last_found <= right) {
        const auto& version = versions[index_last_found];
        if (version->fd <= time && version->td >= time) {
            return version;
        }
    }

    while (left <= right) {
        int mid = left + (right - left) / 2;
        auto const &version = versions[mid];

        if (version->fd <= time && version->td >= time) {
            index_last_found = mid;
            return version;
        }
        if (version->fd < time) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return nullptr;
}

void Object::mergeData() {
    for (int i = 0; i < versions.size() - 1; ++i) {
        if (versions[i]->td > versions[i + 1]->fd) {
            this->setis_valid(false);
        }
    }
}

}} //namespace svyazcom::clr
