cmake_minimum_required(VERSION 3.25)

project(CLAVIS LANGUAGES CXX)

# Set build type (default is Debug)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# NOTE: file(GLOB) is not recommended by CMake official docs.
# Consider listing source files explicitly for reliable rebuilds.
# See: https://cmake.org/cmake/help/latest/command/file.html#glob
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

# Set C++ standard (modern target-based approach)
target_compile_features(clavis_algorithm PUBLIC cxx_std_20)

# Set compiler warnings (target-based, not global CMAKE_CXX_FLAGS)
target_compile_options(clavis_algorithm PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra>
)

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

# Set compiler warnings for tests
target_compile_options(clavis_algorithm_test PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra>
)

# Discover and register tests
include(GoogleTest)
gtest_discover_tests(clavis_algorithm_test)

# =============================================================================
# Code Quality Tools
# =============================================================================

# Collect all C++ files for formatting
file(GLOB_RECURSE ALL_CXX_FILES
  ${CMAKE_SOURCE_DIR}/src/*.hpp
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.h
  ${CMAKE_SOURCE_DIR}/tests/*.cpp
)

# Collect source files only for linting (exclude tests)
file(GLOB_RECURSE SRC_CXX_FILES
  ${CMAKE_SOURCE_DIR}/src/*.hpp
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.h
)

# clang-format targets
find_program(CLANG_FORMAT clang-format
  HINTS
    $ENV{LLVM_DIR}/bin
    /opt/homebrew/opt/llvm/bin
    /usr/local/opt/llvm/bin
    /usr/bin
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
    $ENV{LLVM_DIR}/bin
    /opt/homebrew/opt/llvm/bin
    /usr/local/opt/llvm/bin
    /usr/bin
)
if(CLANG_TIDY)
  add_custom_target(lint
    COMMAND ${CLANG_TIDY}
      -p ${CMAKE_BINARY_DIR}
      -header-filter=${CMAKE_SOURCE_DIR}/src/.*
      ${SRC_CXX_FILES}
      --
      -x c++
      -std=c++20
      -I${CMAKE_SOURCE_DIR}/src
    COMMENT "Running clang-tidy on source files"
    VERBATIM
  )
else()
  message(STATUS "clang-tidy not found. Lint target disabled.")
endif()
