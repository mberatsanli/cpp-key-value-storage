#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

class FileManager {
public:
    FileManager(const std::string& data_dir);
    ~FileManager();

    // File operations
    bool write_block(const std::string& filename, const std::vector<uint8_t>& data, size_t offset);
    bool read_block(const std::string& filename, std::vector<uint8_t>& data, size_t offset, size_t size);
    bool append_block(const std::string& filename, const std::vector<uint8_t>& data);
    
    // File management
    bool create_file(const std::string& filename);
    bool delete_file(const std::string& filename);
    bool file_exists(const std::string& filename) const;
    size_t get_file_size(const std::string& filename) const;

private:
    std::string data_directory;
    static const size_t BLOCK_SIZE = 4096;  // 4KB blocks

    std::string get_full_path(const std::string& filename) const;
};

#endif // FILE_MANAGER_H 