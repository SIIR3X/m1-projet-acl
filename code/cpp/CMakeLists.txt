cmake_minimum_required(VERSION 3.16)

project(projet-acl VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
#                               SOURCES LIB                                   #
###############################################################################
file(GLOB_RECURSE LIB_SOURCES
  src/modele/*.cpp
  src/utils/*.cpp
)

add_library(projet-lib ${LIB_SOURCES})
target_include_directories(projet-lib PUBLIC include)

###############################################################################
#                           EXECUTABLE PRINCIPAL                              #
###############################################################################
add_executable(projet-acl src/main.cpp)
target_link_libraries(projet-acl PRIVATE projet-lib)

###############################################################################
#                                   TESTS                                     #
###############################################################################
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP YES
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_executable(tests ${TEST_SOURCES})
include(GoogleTest)
gtest_discover_tests(tests)
target_link_libraries(tests PRIVATE projet-lib gtest gtest_main)

add_test(NAME allTests COMMAND tests)