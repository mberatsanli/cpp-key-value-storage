#include <gtest/gtest.h>
#include "../src/kvstore.h"
#include <filesystem>

class KVStoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary test directory
        test_dir = std::filesystem::current_path() / "test_data";
        std::filesystem::create_directories(test_dir);
    }

    void TearDown() override {
        // Clean up test directory
        std::filesystem::remove_all(test_dir);
    }

    std::filesystem::path test_dir;
};

TEST_F(KVStoreTest, BasicOperations) {
    KVStore store(test_dir.string());
    
    // Test put and get
    store.put("key1", "value1");
    EXPECT_EQ(store.get("key1"), "value1");
    
    // Test update
    store.put("key1", "value2");
    EXPECT_EQ(store.get("key1"), "value2");
    
    // Test remove
    store.remove("key1");
    EXPECT_THROW(store.get("key1"), std::runtime_error);
}

TEST_F(KVStoreTest, MultipleOperations) {
    KVStore store(test_dir.string());
    
    // Insert multiple key-value pairs
    store.put("key1", "value1");
    store.put("key2", "value2");
    store.put("key3", "value3");
    
    // Verify all values
    EXPECT_EQ(store.get("key1"), "value1");
    EXPECT_EQ(store.get("key2"), "value2");
    EXPECT_EQ(store.get("key3"), "value3");
} 