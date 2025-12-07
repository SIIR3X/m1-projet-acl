cmake_minimum_required(VERSION 3.16)
project(m1-projet-acl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(code/cpp)

add_subdirectory(tests/cpp)