#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <map>
#include <any>
#include <string>
#include <algorithm>

struct Version {
    unsigned int rid = 0;
    time_t fd = 0;
    time_t td = 0;
    std::unordered_map<std::string, std::any> other;
};

struct Object {
    std::string key;
    std::map<std::time_t, Version> versions;
    bool isCorrect = true;

    const Version* findVersion(time_t time) const;

    std::string toString();
};

class DataStore {
private:
    Object* data;
    size_t capacity;
    size_t size;
    int indexLastFound;

    void resize(size_t newCapacity);

public:
    DataStore();
    ~DataStore();

    int getSize();

    void addVersion(const Version& ver, time_t fd, int indexObject);
    void addObject(const Object& obj);
    const std::pair<Object, Version> findVersion(const std::string& key, time_t time);
};