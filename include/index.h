#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>
#include <vector>

struct BTreeNode {
    std::map<std::string, std::vector<int>> keys; // key -> row indices
};

class BTreeIndex {
private:
    BTreeNode root;
    
public:
    BTreeIndex();
    void insert(const std::string& key, int rowIndex);
    void remove(const std::string& key, int rowIndex);
    std::vector<int> search(const std::string& key) const;
    std::vector<int> rangeSearch(const std::string& minKey, const std::string& maxKey) const;
};

#endif // INDEX_H