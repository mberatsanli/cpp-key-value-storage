#include "src/kvstore.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // Initialize KVStore with a data directory
        KVStore store("./data");

        // Example operations
        std::cout << "Performing basic KV operations...\n";

        // Put some values
        store.put("name", "John Doe");
        store.put("age", "30");
        store.put("city", "New York");

        // Retrieve and print values
        std::cout << "name: " << store.get("name") << std::endl;
        std::cout << "age: " << store.get("age") << std::endl;
        std::cout << "city: " << store.get("city") << std::endl;

        // Update a value
        store.put("age", "31");
        std::cout << "Updated age: " << store.get("age") << std::endl;

        // Remove a value
        store.remove("city");
        std::cout << "Removed city entry\n";

        // Try to get non-existent key
        try {
            store.get("city");
        } catch (const std::runtime_error& e) {
            std::cout << "Expected error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 