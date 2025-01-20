#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Build tests
cd build
cmake ..
make run_tests 