#!/bin/bash

# Create data directory if it doesn't exist
mkdir -p data

# Default port
PORT=8080

# Use custom port if provided
if [ $# -ge 1 ]; then
    PORT=$1
fi

# Run the HTTP server
./build/kvserver $PORT 