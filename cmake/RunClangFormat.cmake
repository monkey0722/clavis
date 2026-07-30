cmake_minimum_required(VERSION 3.25)

if(NOT DEFINED CLANG_FORMAT_EXECUTABLE OR CLANG_FORMAT_EXECUTABLE STREQUAL "")
  message(FATAL_ERROR "CLANG_FORMAT_EXECUTABLE is required")
endif()

if(NOT DEFINED CLAVIS_SOURCE_DIR OR CLAVIS_SOURCE_DIR STREQUAL "")
  message(FATAL_ERROR "CLAVIS_SOURCE_DIR is required")
endif()

# Formatting intentionally discovers files at execution time. Unlike build
# sources, this must also cover new files that are not registered with a target.
file(GLOB_RECURSE CLAVIS_FORMAT_FILES
  LIST_DIRECTORIES FALSE
  "${CLAVIS_SOURCE_DIR}/src/*.cpp"
  "${CLAVIS_SOURCE_DIR}/src/*.h"
  "${CLAVIS_SOURCE_DIR}/src/*.hpp"
  "${CLAVIS_SOURCE_DIR}/tests/*.cpp"
  "${CLAVIS_SOURCE_DIR}/tests/*.h"
  "${CLAVIS_SOURCE_DIR}/tests/*.hpp"
)
list(SORT CLAVIS_FORMAT_FILES)

if(NOT CLAVIS_FORMAT_FILES)
  message(FATAL_ERROR "No C++ files found to format")
endif()

if(CLAVIS_FORMAT_CHECK)
  set(CLAVIS_FORMAT_OPTIONS --dry-run --Werror)
else()
  set(CLAVIS_FORMAT_OPTIONS -i)
endif()

execute_process(
  COMMAND
    "${CLANG_FORMAT_EXECUTABLE}"
    ${CLAVIS_FORMAT_OPTIONS}
    ${CLAVIS_FORMAT_FILES}
  COMMAND_ERROR_IS_FATAL ANY
)
