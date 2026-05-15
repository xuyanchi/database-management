#include "index.h"
#include <iostream>

BTreeIndex::BTreeIndex() {}

void BTreeIndex::insert(const std::string& key, int rowIndex) {
    root.keys[key].push_back(rowIndex);
}

void BTreeIndex::remove(const std::string& key, int rowIndex) {
    if (root.keys.find(key) != root.keys.end()) {
        auto& indices = root.keys[key];
        indices.erase(std::remove(indices.begin(), indices.end(), rowIndex), indices.end());
        
        if (indices.empty()) {
            root.keys.erase(key);
        }
    }
}

std::vector<int> BTreeIndex::search(const std::string& key) const {
    if (root.keys.find(key) != root.keys.end()) {
        return root.keys.at(key);
    }
    return {};
}

std::vector<int> BTreeIndex::rangeSearch(const std::string& minKey, const std::string& maxKey) const {
    std::vector<int> result;
    for (const auto& [key, indices] : root.keys) {
        if (key >= minKey && key <= maxKey) {
            result.insert(result.end(), indices.begin(), indices.end());
        }
    }
    return result;
}