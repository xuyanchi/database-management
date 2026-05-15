#include "database.h"
#include "storage_engine.h"
#include "query_executor.h"
#include <iostream>
#include <filesystem>

Database::Database(const std::string& path) : dataPath(path) {
    txnManager = std::make_unique<TransactionManager>();
    std::filesystem::create_directories(path);
}

Database::~Database() {}

void Database::createTable(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& columns) {
    if (tables.find(tableName) != tables.end()) {
        std::cout << "Table " << tableName << " already exists!" << std::endl;
        return;
    }
    
    auto table = std::make_shared<Table>(tableName, columns);
    tables[tableName] = table;
    std::cout << "Table " << tableName << " created successfully!" << std::endl;
}

void Database::dropTable(const std::string& tableName) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table " << tableName << " not found!" << std::endl;
        return;
    }
    
    tables.erase(tableName);
    StorageEngine::deleteTable(dataPath, tableName);
    std::cout << "Table " << tableName << " dropped!" << std::endl;
}

void Database::insert(const std::string& tableName, const Row& row) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table " << tableName << " not found!" << std::endl;
        return;
    }
    
    tables[tableName]->insertRow(row);
    std::cout << "Row inserted into " << tableName << " successfully!" << std::endl;
}

std::vector<Row> Database::select(const std::string& tableName) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table " << tableName << " not found!" << std::endl;
        return {};
    }
    
    return tables[tableName]->searchRows();
}

void Database::update(const std::string& tableName, const std::string& condition, const Row& values) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table " << tableName << " not found!" << std::endl;
        return;
    }
    
    tables[tableName]->updateRows(condition, values);
    std::cout << "Rows updated in " << tableName << " successfully!" << std::endl;
}

void Database::deleteRow(const std::string& tableName, const std::string& condition) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table " << tableName << " not found!" << std::endl;
        return;
    }
    
    tables[tableName]->deleteRows(condition);
    std::cout << "Rows deleted from " << tableName << " successfully!" << std::endl;
}

void Database::createIndex(const std::string& tableName, const std::string& columnName) {
    if (tables.find(tableName) == tables.end()) {
        std::cout << "Table " << tableName << " not found!" << std::endl;
        return;
    }
    
    tables[tableName]->createIndex(columnName);
    std::cout << "Index on " << columnName << " created successfully!" << std::endl;
}

std::vector<Row> Database::query(const std::string& sql) {
    auto parsed = QueryExecutor::parseSQL(sql);
    
    if (tables.find(parsed.tableName) == tables.end()) {
        std::cout << "Table " << parsed.tableName << " not found!" << std::endl;
        return {};
    }
    
    switch (parsed.type) {
        case QueryExecutor::StatementType::SELECT:
            return QueryExecutor::executeSelect(tables[parsed.tableName].get(), parsed);
        case QueryExecutor::StatementType::INSERT:
            QueryExecutor::executeInsert(tables[parsed.tableName].get(), parsed);
            break;
        case QueryExecutor::StatementType::UPDATE:
            QueryExecutor::executeUpdate(tables[parsed.tableName].get(), parsed);
            break;
        case QueryExecutor::StatementType::DELETE:
            QueryExecutor::executeDelete(tables[parsed.tableName].get(), parsed);
            break;
    }
    
    return {};
}

TransactionId Database::beginTransaction() {
    return txnManager->createTransaction();
}

void Database::commit(TransactionId txnId) {
    txnManager->commit(txnId);
    std::cout << "Transaction " << txnId << " committed!" << std::endl;
}

void Database::rollback(TransactionId txnId) {
    txnManager->rollback(txnId);
    std::cout << "Transaction " << txnId << " rolled back!" << std::endl;
}