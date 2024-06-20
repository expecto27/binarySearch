#pragma once

#include <iostream>

#include "Models.h"

class Prices : public Version {
    public:
        inline static const std::string name = "prices";

    private:
        unsigned int id;
        unsigned int plan_id;
        unsigned int conn_type_id;
        std::string  zone_name;
        unsigned int interval_group_id;
        unsigned int trange_group_id;
        unsigned int trange_id;
        unsigned int currency_id;

        unsigned int ctl;
        unsigned int ctl2;
        unsigned int ctl3;
        std::string  service_class;
        double       price;
        double       coef;
        unsigned int fs;
        unsigned int cl;
        unsigned int reprice_mode;
        std::string  p_fd;

    public:
        Prices()
            : id(0),
              plan_id(0),
              conn_type_id(0),
              interval_group_id(0),
              trange_group_id(0),
              trange_id(0),
              currency_id(0),
              ctl(0),
              ctl2(0),
              ctl3(0),
              price(0.0),
              coef(0.0),
              fs(0),
              cl(0),
              reprice_mode(0) {}

        explicit Prices(std::vector<std::string>&& data) {
            if (!data[0].empty()) rid = std::stoul(data[0]);
            if (!data[1].empty()) fd = static_cast<time_t>(std::stoull(data[1]));
            if (!data[2].empty()) td = static_cast<time_t>(std::stoull(data[2]));
            if (!data[4].empty()) id = std::stoul(data[4]);
            if (!data[5].empty()) plan_id = std::stoul(data[5]);
            if (!data[6].empty()) conn_type_id = std::stoul(data[6]);
            if (!data[7].empty()) zone_name = data[7];
            if (!data[8].empty()) interval_group_id = std::stoul(data[8]);
            if (!data[9].empty()) trange_group_id = std::stoul(data[9]);
            if (!data[10].empty()) trange_id = std::stoul(data[10]);
            if (!data[11].empty()) trange_id = std::stoul(data[11]);
            if (!data[12].empty()) currency_id = std::stoul(data[12]);
            if (!data[13].empty()) ctl = std::stoul(data[13]);
            if (!data[14].empty()) ctl2 = std::stoul(data[14]);
            if (!data[15].empty()) ctl3 = std::stoul(data[15]);
            if (!data[16].empty()) service_class = data[16];
            if (!data[17].empty()) price = std::stod(data[17]);
            if (!data[18].empty()) coef = std::stod(data[18]);
            if (!data[19].empty()) fs = std::stoul(data[19]);
            if (!data[20].empty()) cl = std::stoul(data[20]);
            if (!data[21].empty()) reprice_mode = std::stoul(data[21]);
            if (data.size() > 22 && !data[22].empty()) p_fd = data[22];
        }

        std::string toString() const override {
            std::string base_string = Version::toString();

            std::string prices_string =
                " id: " + std::to_string(id) + " plan_id: " + std::to_string(plan_id) +
                " conn_type_id: " + std::to_string(conn_type_id) + " zone_name: " + zone_name +
                " interval_group_id: " + std::to_string(interval_group_id) +
                " trange_group_id: " + std::to_string(trange_group_id) + " trange_id: " + std::to_string(trange_id) +
                " currency_id: " + std::to_string(currency_id) + " ctl1: " + std::to_string(ctl) +
                " ctl2: " + std::to_string(ctl2) + " ctl3: " + std::to_string(ctl3) +
                " service_class: " + service_class + " price: " + std::to_string(price) +
                " coef: " + std::to_string(coef) + " fs: " + std::to_string(fs) + " cl: " + std::to_string(cl) +
                " reprice_mode: " + std::to_string(reprice_mode) + " p_fd: " + p_fd;

            return " ObjectName: Prices " + base_string + prices_string;
        }

        unsigned int getId() const { return id; }
        void         setId(unsigned int value) { id = value; }

        unsigned int getPlanId() const { return plan_id; }
        void         setPlanId(unsigned int value) { plan_id = value; }

        unsigned int getConnTypeId() const { return conn_type_id; }
        void         setConnTypeId(unsigned int value) { conn_type_id = value; }

        const std::string& getZoneName() const { return zone_name; }
        void               setZoneName(const std::string& value) { zone_name = value; }

        unsigned int getIntervalGroupId() const { return interval_group_id; }
        void         setIntervalGroupId(unsigned int value) { interval_group_id = value; }

        unsigned int getTrangeGroupId() const { return trange_group_id; }
        void         setTrangeGroupId(unsigned int value) { trange_group_id = value; }

        unsigned int getTrangeId() const { return trange_id; }
        void         setTrangeId(unsigned int value) { trange_id = value; }

        unsigned int getCurrencyId() const { return currency_id; }
        void         setCurrencyId(unsigned int value) { currency_id = value; }

        unsigned int getCtl1() const { return ctl; }
        void         setCtl1(unsigned int value) { ctl = value; }

        unsigned int getCtl2() const { return ctl2; }
        void         setCtl2(unsigned int value) { ctl2 = value; }

        unsigned int getCtl3() const { return ctl3; }
        void         setCtl3(unsigned int value) { ctl3 = value; }

        const std::string& getServiceClass() const { return service_class; }
        void               setServiceClass(const std::string& value) { service_class = value; }

        double getPrice() const { return price; }
        void   setPrice(double value) { price = value; }

        double getCoef() const { return coef; }
        void   setCoef(double value) { coef = value; }

        unsigned int getFs() const { return fs; }
        void         setFs(unsigned int value) { fs = value; }

        unsigned int getCl() const { return cl; }
        void         setCl(unsigned int value) { cl = value; }

        unsigned int getRepriceMode() const { return reprice_mode; }
        void         setRepriceMode(unsigned int value) { reprice_mode = value; }

        const std::string& getP_fd() const { return p_fd; }
        void               setP_fd(const std::string& value) { p_fd = value; }
};
