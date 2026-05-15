#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "table.h"
#include "transaction_manager.h"

using Row = std::map<std::string, std::string>;

class Database {
private:
    std::string dataPath;
    std::map<std::string, std::shared_ptr<Table>> tables;
    std::unique_ptr<TransactionManager> txnManager;

public:
    Database(const std::string& path);
    ~Database();

    void createTable(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& columns);
    void dropTable(const std::string& tableName);
    void insert(const std::string& tableName, const Row& row);
    std::vector<Row> select(const std::string& tableName);
    void update(const std::string& tableName, const std::string& condition, const Row& values);
    void deleteRow(const std::string& tableName, const std::string& condition);
    void createIndex(const std::string& tableName, const std::string& columnName);
    std::vector<Row> query(const std::string& sql);
    
    TransactionId beginTransaction();
    void commit(TransactionId txnId);
    void rollback(TransactionId txnId);
};

#endif // DATABASE_H