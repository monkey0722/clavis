cmake_minimum_required(VERSION 3.25)

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
  src/math/*.hpp
)

# Collect test files
file(GLOB TEST_SOURCES
  tests/*.cpp
  tests/graph/*.cpp
  tests/data_structure/*.cpp
  tests/sorting/*.cpp
  tests/math/*.cpp
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

# Discover and register tests
include(GoogleTest)
gtest_discover_tests(clavis_algorithm_test)

# =============================================================================
# Code Quality Tools
# =============================================================================

# Collect all C++ files for formatting/linting
file(GLOB_RECURSE ALL_CXX_FILES
  ${CMAKE_SOURCE_DIR}/src/*.hpp
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.h
  ${CMAKE_SOURCE_DIR}/tests/*.cpp
)

# clang-format targets
find_program(CLANG_FORMAT clang-format
  HINTS
    /opt/homebrew/opt/llvm/bin
    /usr/local/opt/llvm/bin
)
if(CLANG_FORMAT)
  add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i ${ALL_CXX_FILES}
    COMMENT "Running clang-format on all files"
    VERBATIM
  )

  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT} --dry-run --Werror ${ALL_CXX_FILES}
    COMMENT "Checking code format"
    VERBATIM
  )
else()
  message(STATUS "clang-format not found. Format targets disabled.")
endif()

# clang-tidy target
find_program(CLANG_TIDY clang-tidy
  HINTS
    /opt/homebrew/opt/llvm/bin
    /usr/local/opt/llvm/bin
)
if(CLANG_TIDY)
  add_custom_target(lint
    COMMAND ${CLANG_TIDY} -p ${CMAKE_BINARY_DIR} ${ALL_CXX_FILES}
    COMMENT "Running clang-tidy"
    VERBATIM
  )
else()
  message(STATUS "clang-tidy not found. Lint target disabled.")
endif()
