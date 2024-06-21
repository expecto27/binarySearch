#pragma once

//FIXME move into types.hpp
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/*! terminalogy
 *
 *  Entity - набор обьектов одной сущности определемых однотипным набором атрибутов и их значений
 *  Object - уникальный обьект сущности, идентифицируемый ключем key
 *  Version - версия обьекта
 *
 */

namespace svyazcom {
namespace clr {

/*!@class Version
 * Object version with unique rid, base class for other entity version
 * @member rid unique identitfier for version
 * @member fd unix time, start of version existance
 * @member td unix time, end if version existsance
 */
class Version {

    typedef std::shared_ptr<Version> version_ptr;

    protected:
        const unsigned int rid;
        const time_t       fd;
        const time_t       td;

    public:
        Version(
            const unsigned int rid,
            const time_t fd,
            const time_t td
        )
        : rid{rid}, fd{fd}, td{td} {}

        virtual ~Version() = default;
};

/*!@concept VersionT
 * Define types derived from Version
 */
template<typename T>
concept VersionT = std::is_base_of_v<Version, T>;

/*!@class Object
 * Objects entitity identified by unique key, consists of vector of verions order by start time
 * @note version must not by overlapped in time [fd:td]
*/
class Object {
    public:
        typedef std::vector<const Version *> versions_t;
        typedef std::unordered_map<unsigned int, const Version*> versions_rid_t;

    private:

        const std::string  key;

        /*!@member versions, vector of object version */
        versions_t      versions;
        /*!@member map of versions by rid */
        versions_rid_t  versions_by_rid;

        bool is_valid;
        int  index_last_found;

        const Version *Search(time_t time);

    public:
        Object() : is_valid(true), index_last_found(-1) {}

        void VersionAdd(const Version *value) {

            if (version->fd <= versions[versions.size()]->td) {
                is_valid = false;
            }
            versions.push_back(value);
            versions_by_rid[value->rid] = value;
        }

        bool is_valid() const { return is_valid; }

        const Version* VersionSearch(time_t time) {
            return search(time);
        }

        Version::version_ptr VersionByRid(unsigned int rid) {
            auto const &it = versions_by_rid.find(rid);
            if (it != versions_by_rid.end()) {
                return it->second;
            }
            return nullptr;
        }
};


}} //namespace svyazcom::clr
