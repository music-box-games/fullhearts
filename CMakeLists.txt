# require cmake version 3.10
cmake_minimum_required(VERSION 3.10)

# set project name
project(fullhearts)

# add include directory
include_directories(src/include)

# add source files
file(GLOB SOURCES "src/*.cpp")

# c++17 compiler flags
if(MSVC)
# /std:c++17 for msvc
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else(MSVC)
# -std=c++17 for clang++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(MSVC)

# set exe output
add_executable(fullhearts ${SOURCES})