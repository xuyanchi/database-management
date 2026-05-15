#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "index.h"

using Row = std::map<std::string, std::string>;
using ColumnDef = std::pair<std::string, std::string>;

class Table {
private:
    std::string tableName;
    std::vector<ColumnDef> columns;
    std::vector<Row> rows;
    std::map<std::string, std::shared_ptr<BTreeIndex>> indexes;

public:
    Table(const std::string& name, const std::vector<ColumnDef>& cols);
    
    void insertRow(const Row& row);
    std::vector<Row> searchRows(const std::string& condition = "");
    void updateRows(const std::string& condition, const Row& values);
    void deleteRows(const std::string& condition);
    void createIndex(const std::string& columnName);
    
    const std::vector<ColumnDef>& getColumns() const;
    const std::vector<Row>& getRows() const;
    std::string getTableName() const;
};

#endif // TABLE_H