cmake_minimum_required(VERSION 3.10)

project(CLAVIS LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect Source Files
file(GLOB CORE_SOURCES
  src/*.cpp
  src/graph/*.hpp
  src/data_structure/*.hpp
  src/sorting/*.hpp
)

# Collect Test Files
file(GLOB TEST_SOURCES
  tests/*.cpp
  tests/graph/*.cpp
  tests/data_structure/*.cpp
  tests/sorting/*.cpp
)

# Integrate All Sources
set(SOURCES ${CORE_SOURCES})

# Create Library
add_library(clavis_algorithm ${SOURCES})

# Google Test Setup
find_package(GTest REQUIRED)
enable_testing()

# Test Execution File
add_executable(clavis_algorithm_test ${TEST_SOURCES})

# Include Directories
target_include_directories(clavis_algorithm_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(clavis_algorithm_test clavis_algorithm GTest::GTest GTest::Main)

# Register Test
add_test(NAME AlgorithmTest COMMAND clavis_algorithm_test)