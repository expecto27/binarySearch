#include "DataStore.h"
#include <algorithm>
#include <utility>

DataStore::DataStore() : capacity(1), size(0), indexLastFound(-1) {
    data = new Object[capacity];
    data[0] = Object();
}

DataStore::~DataStore() {
    delete[] data;
}

void DataStore::resize(size_t newCapacity) {
    Object* newData = new Object[newCapacity];
    size_t newSize = std::min(size, newCapacity);
    for (size_t i = 0; i < newSize; ++i) {
        newData[i] = std::move(data[i]);     }
    delete[] data; 
    data = newData;
    capacity = newCapacity;
    size = newSize;
}


int DataStore::getSize() {
    return this->size;
}

void DataStore::addObject(const Object& obj) {
    if (size >= capacity) {
        resize(capacity * 2); 
    }
    data[size++] = obj; 
}

void DataStore::addVersion(const Version& ver, time_t fd, int indexObject) {
    if (indexObject >= capacity) {
        resize(capacity * 2);
    }
    if (indexObject >= size) {
        size = indexObject + 1; 
    }
    data[indexObject].versions[fd] = ver;
}

const std::pair<Object, Version> DataStore::findVersion(const std::string& key, time_t time) {
    int l = 0;
    int r = size - 1;
    while (l <= r) {
        int mid = (r + l) / 2;
        const Object& obj = data[mid];
        if (obj.key == key) {
            return std::make_pair(obj, *obj.findVersion(time));
        }
        else if (obj.key < key) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return { Object(),Version() };
}

const Version* Object::findVersion(time_t time) const {
    auto it = versions.upper_bound(time);
    if (it != versions.begin()) {
        --it;
        const Version& version = it->second;
        if (time >= it->first && time <= version.td) {
            return &version;
        }
    }
    return nullptr;
}


std::string Object::toString() {
    std::string result = "";
    result += "Key: " + this->key;
    return result;
}