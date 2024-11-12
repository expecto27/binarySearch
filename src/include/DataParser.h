#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataStore.h"

namespace svyazcom {
namespace clr {

namespace DataParser {
    template <VersionT T>
    void ParseRows(csvreader::rows_t&& rows, DataStore& data) {
        std::string carry_key = "";
        fmt::print("parse object {} size {}\n", T::name, rows.size());
        for (auto&& row : rows) {
            object_ptr instance = std::make_shared<Object>();
            instance->setKey(row[3]);
            if (instance->getKey() != carry_key) {
                data.addObject(instance, T::name);
            }
            carry_key = row[3];
            std::shared_ptr<T> version = std::make_shared<T>(std::move(row));
            data.addVersion(version, instance->getKey(), T::name);
        }
    };
}

}} //namespace svyazcom::clr
