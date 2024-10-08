cmake_minimum_required(VERSION 3.14...3.22)

project(Task1Tests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/getCPM.cmake)
set(CPM_DOWNLOAD_ALL ON)
# CPMAddPackage( NAME doctest GITHUB_REPOSITORY "doctest/doctest" VERSION "2.4.9" )
include(../cmake/packages/add_googletest.cmake)
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

if(TEST_INSTALLED_VERSION)
  find_package(Task1 REQUIRED)
else()
  CPMAddPackage(NAME Task1 SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(
  GLOB_RECURSE sources CONFIGURE_DEPENDS
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/source/
  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

foreach(source ${sources})
  string(REPLACE "." "_" name ${source})
  string(REPLACE "/" "_" name ${source})
  add_executable(${PROJECT_NAME}_test_${name} ${CMAKE_CURRENT_SOURCE_DIR}/source/${source})
  target_link_libraries(${PROJECT_NAME}_test_${name} PRIVATE Task1::Task1)
  target_link_libraries(${PROJECT_NAME}_test_${name} PRIVATE gtest_main)
  set_target_properties(${PROJECT_NAME}_test_${name} PROPERTIES CXX_STANDARD 23)
  add_test(NAME ${PROJECT_NAME}_test_${name} COMMAND ${PROJECT_NAME}_test_${name})
endforeach()
# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(Task1 PUBLIC -Wall -Wpedantic -Wextra)
  elseif(MSVC)
    target_compile_options(Task1 PUBLIC /W4 /WX)
    # target_compile_definitions(${PROJECT_NAME} PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add Task1Tests ----

enable_testing()

# Note: doctest and similar testing frameworks can automatically configure CMake tests. For other
# testing frameworks add the tests target instead: add_test(NAME ${PROJECT_NAME} COMMAND
# ${PROJECT_NAME})

# if(NOT DEFINED doctest_ADDED OR "${doctest_ADDED}" STREQUAL "")
# include("/usr/lib64/cmake/doctest/doctest.cmake") else()
# include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake) endif()
# doctest_discover_tests(${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(Task1 PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(Task1 PUBLIC -fprofile-arcs -ftest-coverage)
endif()
