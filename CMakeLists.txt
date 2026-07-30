cmake_minimum_required(VERSION 3.25)

project(CLAVIS LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

function(clavis_enable_warnings target)
  target_compile_options(${target} PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra>
  )
endfunction()

add_library(clavis_algorithm)
target_compile_features(clavis_algorithm PUBLIC cxx_std_20)
target_include_directories(clavis_algorithm PUBLIC
  ${PROJECT_SOURCE_DIR}/src
)
clavis_enable_warnings(clavis_algorithm)

add_executable(clavis_sorting_example)
target_link_libraries(clavis_sorting_example PRIVATE clavis_algorithm)
clavis_enable_warnings(clavis_sorting_example)

add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
  find_package(GTest REQUIRED)

  add_executable(clavis_algorithm_test)
  target_link_libraries(clavis_algorithm_test PRIVATE
    clavis_algorithm
    GTest::gtest_main
  )
  clavis_enable_warnings(clavis_algorithm_test)

  add_subdirectory(tests)

  include(GoogleTest)
  gtest_discover_tests(clavis_algorithm_test)
endif()

# =============================================================================
# Code Quality Tools
# =============================================================================

get_target_property(CLAVIS_LIBRARY_SOURCES clavis_algorithm SOURCES)
get_target_property(CLAVIS_EXAMPLE_SOURCES clavis_sorting_example SOURCES)
set(CLAVIS_SOURCE_FILES
  ${CLAVIS_LIBRARY_SOURCES}
  ${CLAVIS_EXAMPLE_SOURCES}
)

set(CLAVIS_ALL_CXX_FILES
  ${CLAVIS_SOURCE_FILES}
)
if(BUILD_TESTING)
  get_target_property(CLAVIS_TEST_SOURCES clavis_algorithm_test SOURCES)
  list(APPEND CLAVIS_ALL_CXX_FILES ${CLAVIS_TEST_SOURCES})
endif()

find_program(CLANG_FORMAT clang-format
  HINTS
    $ENV{LLVM_DIR}/bin
    /opt/homebrew/opt/llvm/bin
    /usr/local/opt/llvm/bin
    /usr/bin
)
if(CLANG_FORMAT)
  add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i ${CLAVIS_ALL_CXX_FILES}
    COMMENT "Running clang-format on all files"
    VERBATIM
  )

  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT} --dry-run --Werror ${CLAVIS_ALL_CXX_FILES}
    COMMENT "Checking code format"
    VERBATIM
  )
else()
  message(STATUS "clang-format not found. Format targets disabled.")
endif()

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
      --quiet
      ${CLAVIS_SOURCE_FILES}
      --
      -x c++
      -std=c++20
      -I${PROJECT_SOURCE_DIR}/src
    COMMENT "Running clang-tidy on source files"
    VERBATIM
  )
else()
  message(STATUS "clang-tidy not found. Lint target disabled.")
endif()
