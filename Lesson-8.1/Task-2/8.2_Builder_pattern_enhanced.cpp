#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include <map>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns_.push_back(column);
        return *this;
    }

    // NEW: add several columns
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        columns_.insert(columns_.end(), columns.begin(), columns.end());
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

    // NEW: add several conditions in WHERE using map method
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& pair : kv) {
            where_conditions_.emplace_back(pair.first, pair.second);
        }
        return *this;
    }

    std::string BuildQuery() const {
        std::ostringstream oss;

        oss << "SELECT ";

        //  use * if columns not added
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

        if (!table_.empty()) {
            oss << " FROM " << table_;
        }

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
    // first task functionality
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::string expected = "SELECT name, phone FROM students WHERE id=42 AND name=John;";
    std::string actual = query_builder.BuildQuery();
    assert(actual == expected);

    // second task functionality
    SqlSelectQueryBuilder new_builder;
    std::vector<std::string> cols = { "name", "position", "club" };
    new_builder.AddColumns(cols); // add several columns
    new_builder.AddFrom("students");

    std::map<std::string, std::string> conditions = {
        {"name", "Jack"},
        {"position", "midfielder"},
        {"club", "Krasniy kirpich"}
    };
    new_builder.AddWhere(conditions); // add several conditions

    std::string new_expected = "SELECT name, position, club FROM students WHERE club=Krasniy kirpich AND name=Jack AND position=midfielder;";
    std::string new_actual = new_builder.BuildQuery();
    assert(new_actual == new_expected);

    std::cout << "All tests passed!" << std::endl;
    
    std::cout << "actual   " << new_actual << std::endl;
    std::cout << "expected " << new_expected << std::endl;

    return 0;
}
