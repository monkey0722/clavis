#!/bin/bash
set -eux

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

cd build

# CMake configuration
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_CXX_STANDARD=20 \
      -DCMAKE_CXX_STANDARD_REQUIRED=ON \
      ..

# Build
cmake --build . -- -j"$(nproc)"

# Run tests via CTest
GTEST_COLOR=1 ctest --verbose --output-on-failure
