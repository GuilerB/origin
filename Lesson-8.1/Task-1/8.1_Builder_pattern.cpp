#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns_.push_back(column);
        return *this; 
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_conditions_.emplace_back(column, value);
        return *this;
    }
    
    std::string BuildQuery() const {
        std::ostringstream oss;

        // query beginning
        oss << "SELECT ";

        // use * if columns not added
        if (columns_.empty()) {
            oss << "*";
        }
        else {
            // otherwise add columns with ","
            for (size_t i = 0; i < columns_.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << columns_[i];
            }
        }

        // FROM
        if (!table_.empty()) {
            oss << " FROM " << table_;
        }

        // WHERE
        if (!where_conditions_.empty()) {
            oss << " WHERE ";
            for (size_t i = 0; i < where_conditions_.size(); ++i) {
                if (i > 0) oss << " AND ";
                oss << where_conditions_[i].first << "=" << where_conditions_[i].second;
            }
        }

        oss << ";";

        return oss.str();
    }

private:
    std::vector<std::string> columns_;
    std::string table_;
    std::vector<std::pair<std::string, std::string>> where_conditions_;
};

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    // use an ordinary check, no static_assert
    std::string expected = "SELECT name, phone FROM students WHERE id=42 AND name=John;";
    std::string actual = query_builder.BuildQuery();
    assert(actual == expected);

    return 0;
}