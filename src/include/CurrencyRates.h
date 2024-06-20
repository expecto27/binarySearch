#pragma once
#include "Models.h"
#include "iostream"

class CurrencyRates : public Version {
    public:
        inline static const std::string name = "currency_rates";

    private:
        unsigned int from_id;
        unsigned int to_id;
        double       rate;

    public:
        CurrencyRates() {}

        explicit CurrencyRates(std::vector<std::string>&& data) {
            if (!data[0].empty()) rid = std::stoul(data[0]);
            if (!data[1].empty()) fd = static_cast<time_t>(std::stoull(data[1]));
            if (!data[2].empty()) td = static_cast<time_t>(std::stoull(data[2]));
            if (!data[4].empty()) from_id = std::stoul(data[4]);
            if (!data[5].empty()) to_id = std::stoul(data[5]);
            if (data.size() > 6 && !data[6].empty()) rate = std::stod(data[6]);
        }

        std::string toString() const override {
            std::string base_string = Version::toString();

            std::string currencyRates_string = " from_id: " + std::to_string(from_id) +
                                               " to_id: " + std::to_string(to_id) + " rate: " + std::to_string(rate);

            return " ObjectName: CurrencyRates" + base_string + currencyRates_string;
        }

        unsigned int getFromId() const { return from_id; }
        unsigned int getToId() const { return to_id; }
        double       getRate() const { return rate; }

        void setFromId(unsigned int value) { from_id = value; }
        void setToId(unsigned int value) { to_id = value; }
        void setRate(double value) { rate = value; }
};
