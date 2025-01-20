#ifndef WAL_H
#define WAL_H

#include <string>
#include <fstream>
#include <vector>

enum class LogOperation {
    PUT,
    REMOVE
};

struct LogEntry {
    LogOperation op;
    std::string key;
    std::string value;
    uint64_t timestamp;
};

class WALLogger {
public:
    WALLogger(const std::string& log_path);
    ~WALLogger();

    void log_put(const std::string& key, const std::string& value);
    void log_remove(const std::string& key);
    std::vector<LogEntry> recover();

private:
    std::string log_file_path;
    std::ofstream log_stream;
    
    void write_log_entry(const LogEntry& entry);
};

#endif // WAL_H 