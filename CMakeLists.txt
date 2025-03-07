cmake_minimum_required(VERSION 3.10)

project(CLAVIS LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build type (default is Debug)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Basic compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Collect source files
file(GLOB CORE_SOURCES
  src/*.cpp
  src/graph/*.hpp
  src/data_structure/*.hpp
  src/sorting/*.hpp
)

# Collect test files
file(GLOB TEST_SOURCES
  tests/*.cpp
  tests/graph/*.cpp
  tests/data_structure/*.cpp
  tests/sorting/*.cpp
)

# Combine all sources
set(SOURCES ${CORE_SOURCES})

# Create library
add_library(clavis_algorithm ${SOURCES})

# Set include directories
target_include_directories(clavis_algorithm PUBLIC
  ${CMAKE_SOURCE_DIR}/src
)

# Google Test configuration
find_package(GTest REQUIRED)
enable_testing()

# Test executable
add_executable(clavis_algorithm_test ${TEST_SOURCES})

# Set include directories for tests
target_include_directories(clavis_algorithm_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(clavis_algorithm_test clavis_algorithm GTest::GTest GTest::Main)

# Register test
add_test(NAME AlgorithmTest COMMAND clavis_algorithm_test)
