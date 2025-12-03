cmake_minimum_required(VERSION 3.16)
project(m1-projet-acl LANGUAGES CXX)

# Utilisation de C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclusion du répertoire contenant le code C++
add_subdirectory(code/cpp)

# Inclusion du répertoir contenant le code des tests C++
add_subdirectory(tests/cpp)