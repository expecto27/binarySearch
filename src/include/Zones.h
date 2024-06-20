#pragma once

#include <iostream>

#include "Models.h"

namespace svyazcom {
namespace clr {

class Zones : public Version {
    public:
        inline static const std::string name = "zones";

    private:
        unsigned int id;
        std::string  zone_name;
        std::string  direction_name;
        std::string  distribution_name;
        unsigned int operator_id;
        unsigned int operator_zone_id;
        unsigned int conn_type_id;

    public:
        Zones() : id(0), operator_id(0), operator_zone_id(0), conn_type_id(0) {}

        explicit Zones(csvreader::row_t&& data) {
            if (!data[0].empty()) rid = std::stoul(data[0]);
            if (!data[1].empty()) fd = static_cast<time_t>(std::stoull(data[1]));
            if (!data[2].empty()) td = static_cast<time_t>(std::stoull(data[2]));
            if (!data[4].empty()) id = std::stoul(data[4]);
            if (!data[5].empty()) zone_name = data[5];
            if (!data[6].empty()) direction_name = data[6];
            if (!data[7].empty()) distribution_name = data[7];
            if (!data[8].empty()) operator_id = std::stoul(data[8]);
            if (!data[9].empty()) operator_zone_id = std::stoul(data[9]);
            if (data.size() > 10 && !data[10].empty()) conn_type_id = std::stoul(data[10]);
        }
        std::string toString() const override {
            std::string base_string = Version::toString();

            std::string zones_string =
                " id: " + std::to_string(id) + " zone_name: " + zone_name + " direction_name: " + direction_name +
                " distribution_name: " + distribution_name + " operator_id: " + std::to_string(operator_id) +
                " operator_zone_id: " + std::to_string(operator_zone_id) +
                " conn_type_id: " + std::to_string(conn_type_id);

            return " ObjectName: Zones " + base_string + zones_string;
        }

        unsigned int getId() const { return id; }
        void         setId(unsigned int value) { id = value; }

        const std::string& getZoneName() const { return zone_name; }
        void               setZoneName(const std::string& value) { zone_name = value; }

        const std::string& getDirectionName() const { return direction_name; }
        void               setDirectionName(const std::string& value) { direction_name = value; }

        const std::string& getDistributionName() const { return distribution_name; }
        void               setDistributionName(const std::string& value) { distribution_name = value; }

        unsigned int getOperatorId() const { return operator_id; }
        void         setOperatorId(unsigned int value) { operator_id = value; }

        unsigned int getOperatorZoneId() const { return operator_zone_id; }
        void         setOperatorZoneId(unsigned int value) { operator_zone_id = value; }

        unsigned int getConnTypeId() const { return conn_type_id; }
        void         setConnTypeId(unsigned int value) { conn_type_id = value; }
};

}} //namespace svyazcom::clr
