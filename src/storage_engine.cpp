#include "storage_engine.h"
#include <fstream>
#include <filesystem>
#include <iostream>

void StorageEngine::saveTable(const std::string& path, const std::string& tableName, const std::vector<Row>& rows) {
    std::string filePath = getTableFilePath(path, tableName);
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filePath << " for writing" << std::endl;
        return;
    }
    
    // Simple CSV format
    for (const auto& row : rows) {
        for (const auto& [key, value] : row) {
            file << key << ":" << value << ";";
        }
        file << "\n";
    }
    
    file.close();
}

std::vector<Row> StorageEngine::loadTable(const std::string& path, const std::string& tableName) {
    std::vector<Row> rows;
    std::string filePath = getTableFilePath(path, tableName);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return rows;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        Row row;
        size_t pos = 0;
        
        while (pos < line.length()) {
            size_t colonPos = line.find(':', pos);
            if (colonPos == std::string::npos) break;
            
            std::string key = line.substr(pos, colonPos - pos);
            
            size_t semiPos = line.find(';', colonPos);
            if (semiPos == std::string::npos) break;
            
            std::string value = line.substr(colonPos + 1, semiPos - colonPos - 1);
            row[key] = value;
            
            pos = semiPos + 1;
        }
        
        if (!row.empty()) {
            rows.push_back(row);
        }
    }
    
    file.close();
    return rows;
}

bool StorageEngine::tableExists(const std::string& path, const std::string& tableName) {
    std::string filePath = getTableFilePath(path, tableName);
    return std::filesystem::exists(filePath);
}

void StorageEngine::deleteTable(const std::string& path, const std::string& tableName) {
    std::string filePath = getTableFilePath(path, tableName);
    if (std::filesystem::exists(filePath)) {
        std::filesystem::remove(filePath);
    }
}

std::string StorageEngine::getTableFilePath(const std::string& path, const std::string& tableName) {
    return path + "/" + tableName + ".db";
}