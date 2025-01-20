#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Build main executable
cd build
cmake ..
make kvstorage 