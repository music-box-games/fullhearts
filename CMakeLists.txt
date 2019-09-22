# require cmake version 3.10
cmake_minimum_required(VERSION 3.10.2)

##################
# set project name
##################
project(fullhearts)

###########################
# add dirs to include paths
###########################
include_directories(src/include)
include_directories(${Boost_INCLUDE_DIR})

##################
# add source files
##################
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

# LIBRARIES 
# find boost LIBRARIES

if(WIN32)
endif(WIN32)

if(UNIX)
FIND_PACKAGE(Boost 1.65.1 COMPONENTS thread REQUIRED)
TARGET_LINK_LIBRARIES(fullhearts LINK_PUBLIC ${Boost_LIBRARIES})
endif(UNIX)