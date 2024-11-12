#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace csvreader {

typedef std::string field_t;
typedef std::vector<field_t> row_t;
typedef std::vector<row_t> rows_t;

class CsvReader {
    public:
        static rows_t ReadFile(const std::string& filename);

    private:
        static row_t SplitRaw(const std::string& raw_data, char separator);
        static field_t RemoveQuotes(const field_t& str);
};

} // namespace csvreader {
