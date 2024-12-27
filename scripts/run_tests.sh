#!/bin/bash

# Usage
if [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
  echo "Usage: ./run_tests.sh [test_name]"
  echo "Options:"
  echo "  --help, -h    Show this help"
  echo "  test_name     Run specific test (e.g., ./tests/sorting/shell_sort_test.cpp)"
  exit 0
fi

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

# Test execution
if [ -f "./algorithm_test" ]; then
  if [ -n "$1" ]; then
    test_file=$(basename "$1") # Get filename without path
    test_name=$(echo "$test_file" | sed 's/_test\.cpp$//') # Remove _test.cpp
    # Convert snake_case to CamelCase
    test_suite=$(echo "$test_name" | perl -pe 's/(^|_)./uc($&)/ge; s/_//g')"Test"

    echo "Running test suite: $test_suite"
    ./algorithm_test --gtest_filter="$test_suite.*"
  else
    ./algorithm_test
  fi
else
  echo "Test executable not found"
fi
