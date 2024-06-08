#pragma once
#include "iostream"
#include "Models.h"

class CurrencyRates : public Version {
private:
    unsigned int from_id;
    unsigned int to_id;
    double rate;

public:
    CurrencyRates() {}

    std::string toString() const override {
        std::string base_string = Version::toString();

        std::string currencyRates_string = " from_id: " + std::to_string(from_id) +
            " to_id: " + std::to_string(to_id) +
            " rate: " + std::to_string(rate);

        return  " ObjectName: CurrencyRates" + base_string + currencyRates_string;
    }

    unsigned int getFromId() const { return from_id; }
    unsigned int getToId() const { return to_id; }
    double getRate() const { return rate; }

    void setFromId(unsigned int value) { from_id = value; }
    void setToId(unsigned int value) { to_id = value; }
    void setRate(double value) { rate = value; }

};
