#pragma once

#include<iostream>

#include "Models.h"

class TcRelationTap : public Version {
private:
    unsigned int tax_profile;
    unsigned int service_profile;
    unsigned int tp_check;
    unsigned int check_mode;
    unsigned int tp_reprice;
    unsigned int transit_tap_mode;
    std::string transit_start;
    std::string transit_end;
    unsigned int transit_period;
    bool gen_rap;
    bool transit_rap;
    bool pass_rc_less_ic;
    unsigned int iot_threshold;
    unsigned int iot_debug;

public:
    TcRelationTap() {}

    TcRelationTap(const std::vector<std::string>& data) {
        if (!data.at(0).empty()) rid = std::stoul(data.at(0));
        if (!data.at(1).empty()) fd = static_cast<time_t>(std::stoull(data.at(1)));
        if (!data.at(2).empty()) td = static_cast<time_t>(std::stoull(data.at(2)));
        if (!data.at(4).empty()) tax_profile = std::stoul(data.at(4));
        if (!data.at(5).empty()) service_profile = std::stoul(data.at(5));
        if (!data.at(6).empty()) tp_check = std::stoul(data.at(6));
        if (!data.at(7).empty()) check_mode = std::stoul(data.at(7));
        if (!data.at(8).empty()) tp_reprice = std::stoul(data.at(8));
        if (!data.at(9).empty()) transit_tap_mode = std::stoul(data.at(9));
        if (!data.at(10).empty()) transit_start = data.at(10);
        if (!data.at(11).empty()) transit_end = data.at(11);
        if (!data.at(12).empty()) transit_period = std::stoul(data.at(12));
        if (!data.at(13).empty()) gen_rap = (data.at(13) == "1");
        if (!data.at(14).empty()) transit_rap = (data.at(14) == "1");
        if (!data.at(15).empty()) pass_rc_less_ic = (data.at(15) == "1");
        if (data.size() > 16 && !data.at(16).empty()) iot_threshold = std::stoul(data.at(16));
        if (data.size() > 17 && !data.at(17).empty()) iot_debug = std::stoul(data.at(17));
    }

    std::string toString() const override {
        std::string base_string = Version::toString();

        std::string tap_string = " tax_profile: " + std::to_string(tax_profile) +
            " service_profile: " + std::to_string(service_profile) +
            " tp_check: " + std::to_string(tp_check) +
            " check_mode: " + std::to_string(check_mode) +
            " tp_reprice: " + std::to_string(tp_reprice) +
            " transit_tap_mode: " + std::to_string(transit_tap_mode) +
            " transit_start: " + transit_start +
            " transit_end: " + transit_end +
            " transit_period: " + std::to_string(transit_period) +
            " gen_rap: " + (gen_rap ? "1" : "0") +
            " transit_rap: " + (transit_rap ? "1" : "0") +
            " pass_rc_less_ic: " + (pass_rc_less_ic ? "1" : "0") +
            " iot_threshold: " + std::to_string(iot_threshold) +
            " iot_debug: " + std::to_string(iot_debug);

        return " ObjectName: TcRelationsTap " + base_string + tap_string;
    }
    unsigned int getTaxProfile() const { return tax_profile; }
    void setTaxProfile(unsigned int value) { tax_profile = value; }

    unsigned int getServiceProfile() const { return service_profile; }
    void setServiceProfile(unsigned int value) { service_profile = value; }

    unsigned int getTpCheck() const { return tp_check; }
    void setTpCheck(unsigned int value) { tp_check = value; }

    unsigned int getCheckMode() const { return check_mode; }
    void setCheckMode(unsigned int value) { check_mode = value; }

    unsigned int getTpReprice() const { return tp_reprice; }
    void setTpReprice(unsigned int value) { tp_reprice = value; }

    unsigned int getTransitTapMode() const { return transit_tap_mode; }
    void setTransitTapMode(unsigned int value) { transit_tap_mode = value; }

    const std::string& getTransitStart() const { return transit_start; }
    void setTransitStart(const std::string& value) { transit_start = value; }

    const std::string& getTransitEnd() const { return transit_end; }
    void setTransitEnd(const std::string& value) { transit_end = value; }

    unsigned int getTransitPeriod() const { return transit_period; }
    void setTransitPeriod(unsigned int value) { transit_period = value; }

    bool getGenRap() const { return gen_rap; }
    void setGenRap(bool value) { gen_rap = value; }

    bool getTransitRap() const { return transit_rap; }
    void setTransitRap(bool value) { transit_rap = value; }

    bool getPassRcLessIc() const { return pass_rc_less_ic; }
    void setPassRcLessIc(bool value) { pass_rc_less_ic = value; }

    unsigned int getIotThreshold() const { return iot_threshold; }
    void setIotThreshold(unsigned int value) { iot_threshold = value; }

    unsigned int getIotDebug() const { return iot_debug; }
    void setIotDebug(unsigned int value) { iot_debug = value; }
};

