#pragma once

//FIXME move into types.hpp
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace svyazcom {
namespace clr {

class Version {

    typedef std::shared_ptr<Version> version_ptr;

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
    public:
        typedef std::shared_prt<Object> object_ptr;
        typedef std::vector<Version::version_ptr> versions_t;
        typedef std::unordered_map<unsigned int, Version::version_ptr> versions_rid_t;

    private:
        std::string  key;
        int          index_last_found;
        versions_t   versions;
        bool         is_valid;

        versions_rid versions_by_rid;

        Version::version_ptr binarySearch(time_t time);

    public:
        Object() : is_valid(true), index_last_found(-1) {}
        const std::string& getKey() const { return key; }
        void               setKey(const std::string& value) { key = value; }

        void addVersions(Version::version_ptr value) {
            versions.push_back(value);
            versions_by_rid[value->getRid()] = value;
        }

        void mergeData();
        bool getis_valid() const { return is_valid; }
        void setis_valid(bool value) { is_valid = value; }

        Version::version_ptr VersionSearch(time_t time) { return binarySearch(time); }

        Version::version_ptr VersionByRid(unsigned int rid) {
            auto const &it = versions_by_rid.find(rid);
            if (it != versions_by_rid.end()) {
                return it->second;
            }
            return nullptr;
        }
        std::string toString();
};


}} //namespace svyazcom::clr
