#include "wal.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

WALLogger::WALLogger(const std::string& log_path) : log_file_path(log_path) {
    // Create directory if it doesn't exist
    std::filesystem::path path(log_file_path);
    std::filesystem::create_directories(path.parent_path());
    
    log_stream.open(log_file_path, std::ios::app | std::ios::binary);
    if (!log_stream) {
        throw std::runtime_error("Failed to open WAL file: " + log_file_path);
    }
}

WALLogger::~WALLogger() {
    if (log_stream.is_open()) {
        log_stream.close();
    }
}

void WALLogger::log_put(const std::string& key, const std::string& value) {
    LogEntry entry;
    entry.op = LogOperation::PUT;
    entry.key = key;
    entry.value = value;
    entry.timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    
    write_log_entry(entry);
}

void WALLogger::log_remove(const std::string& key) {
    LogEntry entry;
    entry.op = LogOperation::REMOVE;
    entry.key = key;
    entry.timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    
    write_log_entry(entry);
}

void WALLogger::write_log_entry(const LogEntry& entry) {
    // Simple serialization format:
    // [timestamp][op][key_size][key][value_size][value]
    
    if (!log_stream) {
        throw std::runtime_error("WAL file is not open");
    }
    
    // Write timestamp
    log_stream.write(reinterpret_cast<const char*>(&entry.timestamp), sizeof(entry.timestamp));
    
    // Write operation
    char op = static_cast<char>(entry.op);
    log_stream.write(&op, sizeof(op));
    
    // Write key
    uint32_t key_size = entry.key.size();
    log_stream.write(reinterpret_cast<const char*>(&key_size), sizeof(key_size));
    log_stream.write(entry.key.c_str(), key_size);
    
    // Write value (only for PUT operations)
    if (entry.op == LogOperation::PUT) {
        uint32_t value_size = entry.value.size();
        log_stream.write(reinterpret_cast<const char*>(&value_size), sizeof(value_size));
        log_stream.write(entry.value.c_str(), value_size);
    }
    
    log_stream.flush();
}

std::vector<LogEntry> WALLogger::recover() {
    std::vector<LogEntry> entries;
    std::ifstream file(log_file_path, std::ios::binary);
    
    if (!file) {
        return entries;  // Return empty vector if file doesn't exist
    }
    
    while (file.peek() != EOF) {
        LogEntry entry;
        
        // Read timestamp
        if (!file.read(reinterpret_cast<char*>(&entry.timestamp), sizeof(entry.timestamp))) {
            break;
        }
        
        // Read operation
        char op;
        if (!file.read(&op, sizeof(op))) {
            break;
        }
        entry.op = static_cast<LogOperation>(op);
        
        // Read key
        uint32_t key_size;
        if (!file.read(reinterpret_cast<char*>(&key_size), sizeof(key_size))) {
            break;
        }
        
        std::vector<char> key_buffer(key_size);
        if (!file.read(key_buffer.data(), key_size)) {
            break;
        }
        entry.key = std::string(key_buffer.data(), key_size);
        
        // Read value (only for PUT operations)
        if (entry.op == LogOperation::PUT) {
            uint32_t value_size;
            if (!file.read(reinterpret_cast<char*>(&value_size), sizeof(value_size))) {
                break;
            }
            
            std::vector<char> value_buffer(value_size);
            if (!file.read(value_buffer.data(), value_size)) {
                break;
            }
            entry.value = std::string(value_buffer.data(), value_size);
        }
        
        entries.push_back(entry);
    }
    
    return entries;
} 