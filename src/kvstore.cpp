#include "kvstore.h"
#include "storage/lsm_tree.h"
#include <stdexcept>

KVStore::KVStore(const std::string& db_path) 
    : wal(db_path + "/wal") {
    recover_from_wal();
}

KVStore::~KVStore() {
    // Cleanup resources
}

void KVStore::put(const std::string& key, const std::string& value) {
    try {
        // Log the operation first
        wal.log_put(key, value);
        
        // Then perform the actual operation
        storage[key] = value;
        
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to put key-value pair: " + std::string(e.what()));
    }
}

std::string KVStore::get(const std::string& key) {
    try {
        auto it = storage.find(key);
        if (it == storage.end()) {
            throw std::runtime_error("Key not found: " + key);
        }
        return it->second;
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to get value for key: " + std::string(e.what()));
    }
}

void KVStore::remove(const std::string& key) {
    try {
        // Log the operation first
        wal.log_remove(key);
        
        // Then perform the actual operation
        if (storage.erase(key) == 0) {
            throw std::runtime_error("Key not found: " + key);
        }
        
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to remove key: " + std::string(e.what()));
    }
}

void KVStore::recover_from_wal() {
    auto entries = wal.recover();
    for (const auto& entry : entries) {
        if (entry.op == LogOperation::PUT) {
            storage[entry.key] = entry.value;
        } else if (entry.op == LogOperation::REMOVE) {
            storage.erase(entry.key);
        }
    }
} 