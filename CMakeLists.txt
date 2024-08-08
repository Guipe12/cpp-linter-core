cmake_minimum_required(VERSION 3.10)

# Project name
project(CPPLint VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
add_executable(cpplinter src/main.cpp src/Linter.cpp)

# Include directories
target_include_directories(cpplinter PRIVATE include)