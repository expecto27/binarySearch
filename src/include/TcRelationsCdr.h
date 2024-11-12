#pragma once

#include <iostream>

#include "Models.h"

namespace svyazcom {
namespace clr {

class TcRelationsCdr : public Version {
    public:
        inline static const std::string name = "tc_relations_cdr";

    private:
        unsigned int tp_cdr;
        unsigned int tp_cdr2;
        bool         gprs_union;
        unsigned int gen_tap_mode;
        std::string  transit_start;
        std::string  transit_end;
        unsigned int transit_period;
        unsigned int tap_notification;
        unsigned int task_rid;
        std::string  number_types;

    public:
        TcRelationsCdr() {}

        explicit TcRelationsCdr(csvreader::row_t&& data) {
            if (!data.at(0).empty()) rid = std::stoul(data.at(0));
            if (!data.at(1).empty()) fd = static_cast<time_t>(std::stoull(data.at(1)));
            if (!data.at(2).empty()) td = static_cast<time_t>(std::stoull(data.at(2)));
            if (!data.at(4).empty()) tp_cdr = std::stoul(data.at(4));
            if (!data.at(5).empty()) tp_cdr2 = std::stoul(data.at(5));
            if (!data.at(6).empty()) gprs_union = (data.at(6) == "1");
            if (!data.at(7).empty()) gen_tap_mode = std::stoul(data.at(7));
            if (!data.at(8).empty()) transit_start = data.at(8);
            if (!data.at(9).empty()) transit_end = data.at(9);
            if (!data.at(10).empty()) transit_period = std::stoul(data.at(10));
            if (!data.at(11).empty()) tap_notification = std::stoul(data.at(11));
            if (!data.at(12).empty()) task_rid = std::stoul(data.at(12));
            if (data.size() > 13 && !data.at(13).empty()) number_types = data.at(13);
        }
        std::string toString() const override {
            std::string base_string = Version::toString();

            std::string cdr_string = " tp_cdr: " + std::to_string(tp_cdr) + " tp_cdr2: " + std::to_string(tp_cdr2) +
                                     " gprs_union: " + (gprs_union ? "true" : "false") +
                                     " gen_tap_mode: " + std::to_string(gen_tap_mode) +
                                     " transit_start: " + transit_start + " transit_end: " + transit_end +
                                     " transit_period: " + std::to_string(transit_period) +
                                     " tap_notification: " + std::to_string(tap_notification) +
                                     " task_rid: " + std::to_string(task_rid) + " number_types: " + number_types;

            return " ObjectName: TcRelationsCdr " + base_string + cdr_string;
        }
        unsigned int getTpCdr() const { return tp_cdr; }
        void         setTpCdr(unsigned int value) { tp_cdr = value; }

        unsigned int getTpCdr2() const { return tp_cdr2; }
        void         setTpCdr2(unsigned int value) { tp_cdr2 = value; }

        bool getGprsUnion() const { return gprs_union; }
        void setGprsUnion(bool value) { gprs_union = value; }

        unsigned int getGenTapMode() const { return gen_tap_mode; }
        void         setGenTapMode(unsigned int value) { gen_tap_mode = value; }

        const std::string& getTransitStart() const { return transit_start; }
        void               setTransitStart(const std::string& value) { transit_start = value; }

        const std::string& getTransitEnd() const { return transit_end; }
        void               setTransitEnd(const std::string& value) { transit_end = value; }

        unsigned int getTransitPeriod() const { return transit_period; }
        void         setTransitPeriod(unsigned int value) { transit_period = value; }

        unsigned int getTapNotification() const { return tap_notification; }
        void         setTapNotification(unsigned int value) { tap_notification = value; }

        unsigned int getTaskRid() const { return task_rid; }
        void         setTaskRid(unsigned int value) { task_rid = value; }

        const std::string& getNumberTypes() const { return number_types; }
        void               setNumberTypes(const std::string& value) { number_types = value; }
};


}} //namespace svyazcom::clr
