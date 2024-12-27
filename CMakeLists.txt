cmake_minimum_required(VERSION 3.10)

project(CLAVIS LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect Source Files
file(GLOB CORE_SOURCES
  src/*.cpp
  src/graph/*.hpp
  src/tree/*.hpp
  src/data_structure/*.hpp
  src/sorting/*.hpp
)

# Collect Test Files
file(GLOB TEST_SOURCES
  tests/*.cpp
  tests/graph/*.cpp
  tests/tree/*.cpp
  tests/data_structure/*.cpp
  tests/sorting/*.cpp
)

# Integrate All Sources
set(SOURCES ${CORE_SOURCES})

# Create Library
add_library(algorithm ${SOURCES})

# Google Test Setup
find_package(GTest REQUIRED)
enable_testing()

# Test Execution File
add_executable(algorithm_test ${TEST_SOURCES})

# Include Directories
target_include_directories(algorithm_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/graph
  ${CMAKE_SOURCE_DIR}/src/tree
  ${CMAKE_SOURCE_DIR}/src/data_structure
  ${CMAKE_SOURCE_DIR}/src/sorting
)

target_link_libraries(algorithm_test algorithm GTest::GTest GTest::Main)

# Register Test
add_test(NAME AlgorithmTest COMMAND algorithm_test)