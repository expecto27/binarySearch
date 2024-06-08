#pragma once

#include <iostream>
#include "Models.h"


class TcRelationsCdr : public Version {
private:
    unsigned int tp_cdr;
    unsigned int tp_cdr2;
    bool gprs_union;
    unsigned int gen_tap_mode;
    std::string transit_start;
    std::string transit_end;
    unsigned int transit_period;
    unsigned int tap_notification;
    unsigned int task_rid;
    std::string number_types;

public:
    TcRelationsCdr() {}
    std::string toString() const override {
        std::string base_string = Version::toString();

        std::string cdr_string = " tp_cdr: " + std::to_string(tp_cdr) +
            " tp_cdr2: " + std::to_string(tp_cdr2) +
            " gprs_union: " + (gprs_union ? "true" : "false") +
            " gen_tap_mode: " + std::to_string(gen_tap_mode) +
            " transit_start: " + transit_start +
            " transit_end: " + transit_end +
            " transit_period: " + std::to_string(transit_period) +
            " tap_notification: " + std::to_string(tap_notification) +
            " task_rid: " + std::to_string(task_rid) +
            " number_types: " + number_types;

        return " ObjectName: TcRelationsCdr " + base_string + cdr_string;
    }
    unsigned int getTpCdr() const { return tp_cdr; }
    void setTpCdr(unsigned int value) { tp_cdr = value; }

    unsigned int getTpCdr2() const { return tp_cdr2; }
    void setTpCdr2(unsigned int value) { tp_cdr2 = value; }

    bool getGprsUnion() const { return gprs_union; }
    void setGprsUnion(bool value) { gprs_union = value; }

    unsigned int getGenTapMode() const { return gen_tap_mode; }
    void setGenTapMode(unsigned int value) { gen_tap_mode = value; }

    const std::string& getTransitStart() const { return transit_start; }
    void setTransitStart(const std::string& value) { transit_start = value; }

    const std::string& getTransitEnd() const { return transit_end; }
    void setTransitEnd(const std::string& value) { transit_end = value; }

    unsigned int getTransitPeriod() const { return transit_period; }
    void setTransitPeriod(unsigned int value) { transit_period = value; }

    unsigned int getTapNotification() const { return tap_notification; }
    void setTapNotification(unsigned int value) { tap_notification = value; }

    unsigned int getTaskRid() const { return task_rid; }
    void setTaskRid(unsigned int value) { task_rid = value; }

    const std::string& getNumberTypes() const { return number_types; }
    void setNumberTypes(const std::string& value) { number_types = value; }

};
