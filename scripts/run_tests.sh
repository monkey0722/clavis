#!/bin/bash
set -e  # Exit immediately if a command exits with a non-zero status

# Create build directory (if it doesn't exist)
if [ ! -d "build" ]; then
  mkdir build
fi

cd build

# CMake configuration
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_CXX_STANDARD=20 \
      -DCMAKE_CXX_STANDARD_REQUIRED=ON \
      ..

# Build (using parallel build)
JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)
cmake --build . -- -j"$JOBS"

# Run tests
GTEST_COLOR=1 ctest --verbose --output-on-failure
