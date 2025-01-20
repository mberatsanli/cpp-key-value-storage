# KVStorage - Key-Value Storage Engine

A simple, efficient key-value storage engine written in C++ with HTTP API support. The project implements various storage engine concepts including Write-Ahead Logging (WAL), LSM Trees, and B+ Trees.

## Features

- In-memory key-value storage with disk persistence
- Write-Ahead Logging (WAL) for durability
- HTTP REST API
- JSON support
- Thread-safe operations
- Comprehensive test suite

## Prerequisites

- C++17 compatible compiler
- CMake (>= 3.10)
- Google Test framework
- macOS or Linux operating system

### Installing Dependencies (macOS)

```bash
# Install Google Test
brew install googletest
```

## Building the Project

The project includes several shell scripts to make building and running easier:

```bash
# Build main executable
./build_main.sh

# Build HTTP server
./build_http.sh

# Build tests
./build_test.sh
```

## Running the Project

### Command Line Interface

```bash
# Run the main CLI application
./run_main.sh
```

### HTTP Server

```bash
# Run the HTTP server (default port: 8080)
./run_http.sh

# Run with custom port
./run_http.sh 9090
```

### Running Tests

```bash
# Run the test suite
./run_test.sh
```

## HTTP API Usage

The HTTP server provides a RESTful API for key-value operations:

### Store a Value

```bash
curl -X PUT -H "Content-Type: application/json" \
     -d '{"value":"John Doe"}' \
     http://localhost:8080/api/v1/kv/name
```

### Retrieve a Value

```bash
curl http://localhost:8080/api/v1/kv/name
```

### Delete a Value

```bash
curl -X DELETE http://localhost:8080/api/v1/kv/name
```

## Project Structure

```
.
├── src/
│   ├── storage/
│   │   ├── bplus_tree.h    # B+ Tree implementation
│   │   ├── lsm_tree.h      # LSM Tree implementation
│   │   ├── wal.h           # Write-Ahead Logging
│   │   └── file_manager.h  # Disk I/O management
│   ├── kvstore.h           # Main KV Store interface
│   ├── kvstore.cpp         # KV Store implementation
│   └── http_server.cpp     # HTTP API server
├── include/
│   └── kvstore/            # External dependencies
├── tests/
│   └── test_kvstore.cpp    # Unit tests
├── data/                   # Data storage directory
├── CMakeLists.txt         # CMake configuration
└── main.cpp               # CLI application
```

## Implementation Details

1. **Write-Ahead Logging (WAL)**
   - All operations are logged before execution
   - Ensures durability and crash recovery
   - Binary format for efficiency

2. **Storage Engine**
   - In-memory hash map for fast access
   - Persistent storage using WAL
   - Future support for LSM Tree and B+ Tree

3. **HTTP Server**
   - RESTful API design
   - JSON request/response format
   - Error handling with appropriate HTTP status codes

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details. 