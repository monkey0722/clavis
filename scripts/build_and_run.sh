#!/bin/bash

# Create buiod directory
if [ ! -d "build" ]; then
    mkdir build
fi

# Move to build directory
cd build

# CMake configuration
cmake ..

# Build
make

# Execute tests (assuming execution of algorithm_test)
if [ -f "./algorithm_test" ]; then
  ./algorithm_test
else
  echo "Test executable not found. Build failed or test target missing."
fi
