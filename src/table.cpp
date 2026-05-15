#include "table.h"
#include <iostream>
#include <algorithm>

Table::Table(const std::string& name, const std::vector<ColumnDef>& cols)
    : tableName(name), columns(cols) {}

void Table::insertRow(const Row& row) {
    rows.push_back(row);
    
    // Update indexes
    for (auto& [colName, index] : indexes) {
        if (row.find(colName) != row.end()) {
            index->insert(row.at(colName), rows.size() - 1);
        }
    }
}

std::vector<Row> Table::searchRows(const std::string& condition) {
    if (condition.empty()) {
        return rows;
    }
    
    std::vector<Row> result;
    for (const auto& row : rows) {
        // Simple condition evaluation
        if (condition.find("=") != std::string::npos) {
            auto pos = condition.find("=");
            std::string colName = condition.substr(0, pos);
            std::string value = condition.substr(pos + 1);
            
            if (row.find(colName) != row.end() && row.at(colName) == value) {
                result.push_back(row);
            }
        }
    }
    
    return result;
}

void Table::updateRows(const std::string& condition, const Row& values) {
    for (auto& row : rows) {
        // Simple condition evaluation
        if (condition.find("=") != std::string::npos) {
            auto pos = condition.find("=");
            std::string colName = condition.substr(0, pos);
            std::string value = condition.substr(pos + 1);
            
            if (row.find(colName) != row.end() && row.at(colName) == value) {
                for (const auto& [key, val] : values) {
                    row[key] = val;
                }
            }
        }
    }
}

void Table::deleteRows(const std::string& condition) {
    auto it = rows.begin();
    while (it != rows.end()) {
        if (condition.find("=") != std::string::npos) {
            auto pos = condition.find("=");
            std::string colName = condition.substr(0, pos);
            std::string value = condition.substr(pos + 1);
            
            if (it->find(colName) != it->end() && it->at(colName) == value) {
                it = rows.erase(it);
                continue;
            }
        }
        ++it;
    }
}

void Table::createIndex(const std::string& columnName) {
    if (indexes.find(columnName) != indexes.end()) {
        std::cout << "Index already exists for column " << columnName << std::endl;
        return;
    }
    
    auto index = std::make_shared<BTreeIndex>();
    for (size_t i = 0; i < rows.size(); ++i) {
        if (rows[i].find(columnName) != rows[i].end()) {
            index->insert(rows[i][columnName], i);
        }
    }
    
    indexes[columnName] = index;
}

const std::vector<ColumnDef>& Table::getColumns() const {
    return columns;
}

const std::vector<Row>& Table::getRows() const {
    return rows;
}

std::string Table::getTableName() const {
    return tableName;
}