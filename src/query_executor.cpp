#include "query_executor.h"
#include <sstream>
#include <algorithm>
#include <iostream>

QueryExecutor::ParsedQuery QueryExecutor::parseSQL(const std::string& sql) {
    ParsedQuery query;
    std::string upperSql = sql;
    std::transform(upperSql.begin(), upperSql.end(), upperSql.begin(), ::toupper);
    
    if (upperSql.find("SELECT") != std::string::npos) {
        query.type = StatementType::SELECT;
    } else if (upperSql.find("INSERT") != std::string::npos) {
        query.type = StatementType::INSERT;
    } else if (upperSql.find("UPDATE") != std::string::npos) {
        query.type = StatementType::UPDATE;
    } else if (upperSql.find("DELETE") != std::string::npos) {
        query.type = StatementType::DELETE;
    }
    
    // Simple parsing logic
    size_t fromPos = upperSql.find("FROM");
    if (fromPos != std::string::npos) {
        fromPos += 5;
        size_t endPos = upperSql.find(" ", fromPos);
        if (endPos == std::string::npos) endPos = upperSql.length();
        query.tableName = sql.substr(fromPos, endPos - fromPos);
    }
    
    size_t wherePos = upperSql.find("WHERE");
    if (wherePos != std::string::npos) {
        wherePos += 6;
        query.condition = sql.substr(wherePos);
    }
    
    return query;
}

std::vector<Row> QueryExecutor::executeSelect(Table* table, const ParsedQuery& query) {
    if (query.condition.empty()) {
        return table->searchRows();
    }
    return table->searchRows(query.condition);
}

void QueryExecutor::executeInsert(Table* table, const ParsedQuery& query) {
    if (!query.values.empty()) {
        table->insertRow(query.values[0]);
    }
}

void QueryExecutor::executeUpdate(Table* table, const ParsedQuery& query) {
    if (!query.values.empty() && !query.condition.empty()) {
        table->updateRows(query.condition, query.values[0]);
    }
}

void QueryExecutor::executeDelete(Table* table, const ParsedQuery& query) {
    if (!query.condition.empty()) {
        table->deleteRows(query.condition);
    }
}

bool QueryExecutor::evaluateCondition(const Row& row, const std::string& condition) {
    // Simple condition evaluation
    if (condition.find("=") != std::string::npos) {
        auto pos = condition.find("=");
        std::string colName = condition.substr(0, pos);
        std::string value = condition.substr(pos + 1);
        
        return row.find(colName) != row.end() && row.at(colName) == value;
    }
    return true;
}