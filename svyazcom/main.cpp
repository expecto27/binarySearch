#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <variant>
#include <any>
#include <sstream>
#include <fstream>
#include <string>

#include "DataStore.h"


time_t stotime(const std::string input) {
    
    unsigned long long unixTimestamp = std::stoull(input);

    return static_cast<time_t>(unixTimestamp);
}
 
std::vector<std::string> split(const std::string& str, char separator) {
    std::stringstream stream(str);
    std::vector<std::string> words;
    std::string word;
    while (std::getline(stream, word, separator)) {
        words.push_back(word);
    }
    return words;
}

std::string removeQuotes(std::string str) {
    std::string ans = "";
    for (char c : str) {
        if (c != '\"') {
            ans += c;
        }
    }
    return ans;
}

void addDataFromCsv(DataStore& dataStore, const std::string filename, char separator) {

    std::ifstream stream(filename);
    std::string title;
    std::string line;
    
    if (std::getline(stream, title)) { // читаем заголовок
        std::string carryKey = "";
        auto titleData = split(removeQuotes(title), separator);
        int index = dataStore.getSize();
        while (std::getline(stream, line)) {
            Object instance;
            auto instanceData = split(removeQuotes(line), separator);


            instance.key = instanceData[3];

            if (instance.key != carryKey) {
                index++;
                dataStore.addObject(instance);
            }

            carryKey = instanceData[3];
            Version ver;

            ver.rid = std::stoul(instanceData[0]);
            ver.td = stotime(instanceData[2]);
            ver.fd = stotime(instanceData[1]);

            for (int i = 4; i < instanceData.size(); i++) {
                ver.other[titleData[i]] = instanceData[i];
            }

            dataStore.addVersion(ver, stotime(instanceData[1]), index);

        }
    }
}

std::string anyToString(const std::any& a) {
    try {
        return std::any_cast<std::string>(a);
    }
    catch (const std::bad_any_cast&) {
        std::stringstream ss;
        if (a.type() == typeid(int)) {
            ss << std::any_cast<int>(a);
        }
        else if (a.type() == typeid(double)) {
            ss << std::any_cast<double>(a);
        }
        else if (a.type() == typeid(bool)) {
            ss << std::boolalpha << std::any_cast<bool>(a);
        }
        else {
            return "";
        }
        return ss.str();
    }
}
std::string resultToString(std::pair<Object, Version>& objVer) {
    std::string result = objVer.first.toString();
    result += " rid: " + objVer.second.rid;
    result += " fd: " + std::to_string(objVer.second.fd);
    result += " td: " + std::to_string(objVer.second.td);
    for (std::pair<std::string, std::any> item : objVer.second.other) {
        result += " " + item.first + ": " + anyToString(item.second);
    }
    return result;
}

int main()
{
    DataStore data;
    addDataFromCsv(data, "currency_rates.csv", ';');
    std::pair<Object, Version> result = data.findVersion("202010000000000.202019999999999", stotime("1451606400"));
    std::cout << resultToString(result);
}