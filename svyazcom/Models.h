#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Version {
    protected:
        unsigned int rid;
        time_t       fd;
        time_t       td;

    public:
        Version() : rid(0), fd(0), td(0) {}

        unsigned int getRid() const { return rid; }
        void         setRid(unsigned int value) { rid = value; }

        time_t getFd() const { return fd; }
        void   setFd(time_t value) { fd = value; }

        time_t getTd() const { return td; }
        void   setTd(time_t value) { td = value; }

        virtual std::string toString() const {
            return " rid: " + std::to_string(this->rid) + " fd: " + std::to_string(this->fd) +
                   " td: " + std::to_string(this->td);
        }
};

template<typename T>
concept VersionT = std::is_base_of_v<Version, T>;

class Object {
    private:
        std::string                           key;
        int                                   indexLastFound;
        std::vector<std::shared_ptr<Version>> versions;
        bool                                  isCorrect;

        std::unordered_map<unsigned int, std::shared_ptr<Version>> versionsByRid;

        std::shared_ptr<Version> binarySearch(time_t time);

    public:
        Object() : isCorrect(true), indexLastFound(-1) {}
        const std::string& getKey() const { return key; }
        void               setKey(const std::string& value) { key = value; }

        void addVersions(std::shared_ptr<Version> value) {
            versions.push_back(value);
            versionsByRid[value->getRid()] = value;
        }

        void mergeData();
        bool getIsCorrect() const { return isCorrect; }
        void setIsCorrect(bool value) { isCorrect = value; }

        std::shared_ptr<Version> findVersion(time_t time) { return binarySearch(time); }

        std::shared_ptr<Version> findVersionByRid(unsigned int rid) {
            auto it = versionsByRid.find(rid);
            if (it != versionsByRid.end()) {
                return it->second;
            }
            return nullptr;
        }
        std::string toString();
};
