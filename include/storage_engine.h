#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

#include <string>
#include <vector>
#include <map>

using Row = std::map<std::string, std::string>;

class StorageEngine {
public:
    static void saveTable(const std::string& path, const std::string& tableName, const std::vector<Row>& rows);
    static std::vector<Row> loadTable(const std::string& path, const std::string& tableName);
    static bool tableExists(const std::string& path, const std::string& tableName);
    static void deleteTable(const std::string& path, const std::string& tableName);
    
private:
    static std::string getTableFilePath(const std::string& path, const std::string& tableName);
};

#endif // STORAGE_ENGINE_H