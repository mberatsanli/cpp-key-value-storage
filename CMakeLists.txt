cmake_minimum_required(VERSION 3.10)
project(kvstorage)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/kvstore.cpp
    src/storage/wal.cpp
)

# Add header files
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/kvstore)

# Create main executable
add_executable(kvstorage ${SOURCES} main.cpp)

# Create HTTP server executable
add_executable(kvserver ${SOURCES} src/http_server.cpp)

if(APPLE)
    target_link_libraries(kvserver "-framework CoreFoundation")
    target_link_libraries(kvserver "-framework Security")
endif()

# Testing configuration
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
add_executable(run_tests tests/test_kvstore.cpp ${SOURCES})
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

# Add test
add_test(NAME kvstore_tests COMMAND run_tests) 