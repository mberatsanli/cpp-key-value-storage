#ifndef LSM_TREE_H
#define LSM_TREE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "file_manager.h"

class LSMTree {
private:
    static const size_t MEMTABLE_SIZE = 1024 * 1024;  // 1MB
    std::map<std::string, std::string> memtable;
    std::vector<std::string> sstable_files;
    size_t current_memtable_size;

public:
    LSMTree();
    ~LSMTree();

    void put(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& value);
    bool remove(const std::string& key);

private:
    void flush_memtable();
    void compact_sstables();
    bool search_sstables(const std::string& key, std::string& value);
};

#endif // LSM_TREE_H 