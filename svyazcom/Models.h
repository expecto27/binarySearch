#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Version {
private:
    unsigned int rid;
    time_t fd;
    time_t td;
public:
    Version() : rid(0), fd(0), td(0) {}

    unsigned int getRid() const { return rid; }
    void setRid(unsigned int value) { rid = value; }

    time_t getFd() const { return fd; }
    void setFd(time_t value) { fd = value; }

    time_t getTd() const { return td; }
    void setTd(time_t value) { td = value; }

   virtual std::string toString() const {
       return " rid: " + std::to_string(this->rid) + " fd: " + std::to_string(this->fd) + " td: " + std::to_string(this->td);
   }
};

class Object {
private:
    std::string key;
    int indexLastFound;
    std::vector<std::shared_ptr<Version>> versions;
    bool isCorrect;
    std::shared_ptr<Version> binarySearch(time_t time);
public:
    Object() : isCorrect(true), indexLastFound(-1) {}
    const std::string& getKey() const { return key; }
    void setKey(const std::string& value) { key = value; }

    void addVersions(std::shared_ptr<Version> value) {
        versions.push_back(value);
    }
    void mergeData();
    bool getIsCorrect() const { return isCorrect; }
    void setIsCorrect(bool value) { isCorrect = value; }

    std::shared_ptr<Version> findVersion(time_t time) {
        return binarySearch(time);
    }

    std::string toString();
};

