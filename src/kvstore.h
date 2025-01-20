#ifndef KVSTORE_H
#define KVSTORE_H

#include <string>
#include <unordered_map>
#include "storage/wal.h"

class KVStore {
public:
    KVStore(const std::string& db_path);
    ~KVStore();
    
    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    void remove(const std::string& key);

private:
    WALLogger wal;
    std::unordered_map<std::string, std::string> storage;
    void recover_from_wal();
};

#endif // KVSTORE_H 