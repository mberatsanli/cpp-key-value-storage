#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Build HTTP server
cd build
cmake ..
make kvserver 