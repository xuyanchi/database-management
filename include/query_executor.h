#ifndef QUERY_EXECUTOR_H
#define QUERY_EXECUTOR_H

#include <string>
#include <vector>
#include <map>
#include "table.h"

using Row = std::map<std::string, std::string>;

class QueryExecutor {
public:
    enum class StatementType {
        SELECT,
        INSERT,
        UPDATE,
        DELETE
    };
    
    struct ParsedQuery {
        StatementType type;
        std::string tableName;
        std::vector<std::string> columns;
        std::vector<Row> values;
        std::string condition;
    };
    
    static ParsedQuery parseSQL(const std::string& sql);
    static std::vector<Row> executeSelect(Table* table, const ParsedQuery& query);
    static void executeInsert(Table* table, const ParsedQuery& query);
    static void executeUpdate(Table* table, const ParsedQuery& query);
    static void executeDelete(Table* table, const ParsedQuery& query);

private:
    static bool evaluateCondition(const Row& row, const std::string& condition);
};

#endif // QUERY_EXECUTOR_H