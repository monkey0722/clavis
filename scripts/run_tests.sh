#!/bin/bash

# Usage
if [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
  echo "Usage: ./run_tests.sh [test_name]"
  echo "Options:"
  echo "  --help, -h    Show this help"
  echo "  test_name     Run specific test (e.g., ./tests/sorting/shell_sort_test)"
  exit 0
fi

# Create buiod directory
if [ ! -d "build" ]; then
  mkdir build
fi

# Move to build directory
cd build

# CMake configuration
cmake -DCMAKE_CXX_STANDARD=20 -DCMAKE_CXX_STANDARD_REQUIRED=ON ..

# Build
make

# Test execution
if [ -f "./algorithm_test" ]; then
  if [ -n "$1" ]; then
    # Get the base name and remove all extensions
    base_name=$(basename "$1" | sed 's/\.[^.]*$//')
    
    # Convert to CamelCase
    # First, if there's no underscore, capitalize all parts
    if [[ $base_name != *"_"* ]]; then
      test_suite=$(echo "$base_name" | sed -r 's/(^|_)([a-z])/\U\2/g')"Test"
    else
      # Otherwise, handle snake_case conversion
      test_suite=$(echo "$base_name" | perl -pe 's/(^|_)([a-z])/\u$2/g')"Test"
    fi
    
    echo "Input path: $1"
    echo "Base name: $base_name"
    echo "Test suite: $test_suite"
    
    # Run tests with more complete output
    ./algorithm_test --gtest_filter="$test_suite.*" --gtest_also_run_disabled_tests
  else
    ./algorithm_test
  fi
else
  echo "Test executable not found"
fi
