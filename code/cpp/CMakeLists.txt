cmake_minimum_required(VERSION 3.16)

project(projet-acl-cpp LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
#                               Paths
###############################################################################

set(CPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

###############################################################################
#                               Library sources
###############################################################################

file(GLOB_RECURSE LIB_SOURCES
    ${CPP_ROOT}/src/algorithmes/*.cpp
    ${CPP_ROOT}/src/modele/*.cpp
    ${CPP_ROOT}/src/utils/*.cpp
    ${CPP_ROOT}/src/serveur/*.cpp
    ${CPP_ROOT}/src/factories/*.cpp
    ${CPP_ROOT}/src/carte/*.cpp
)

add_library(projet-lib ${LIB_SOURCES})
target_include_directories(projet-lib PUBLIC ${CPP_ROOT}/include)

if (WIN32)
    target_link_libraries(projet-lib PUBLIC ws2_32)
endif()

###############################################################################
#                               Main executable
###############################################################################

add_executable(programme-cpp ${CPP_ROOT}/src/main.cpp)
target_link_libraries(programme-cpp PRIVATE projet-lib)

if (MINGW)
    target_link_options(programme-cpp PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
endif()


# ###############################################################################
# #                               Tests
# ###############################################################################
# include(FetchContent)

# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
#   DOWNLOAD_EXTRACT_TIMESTAMP YES
# )

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# enable_testing()

# file(GLOB_RECURSE TEST_SOURCES ${CPP_ROOT}/tests/*.cpp)

# add_executable(tests ${TEST_SOURCES})
# target_link_libraries(tests PRIVATE projet-lib gtest gtest_main)

# include(GoogleTest)
# gtest_discover_tests(tests)