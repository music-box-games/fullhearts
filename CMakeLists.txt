############################
# require cmake version 3.10
############################
cmake_minimum_required(VERSION 3.10.2)

set(DBG 1)
if(DBG)
    set(DEBUG 1)
    set(RELEASE 0)
else(DBG)
    set(DEBUG 0)
    set(RELEASE 1)
endif(DBG)

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

######################
# compiler flags
######################
# standard flags
if(MSVC)
else(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall -pedantic")
endif(MSVC)
# c++17
if(MSVC)
    # /std:c++17 for msvc
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else(MSVC)
    # -std=c++17 for clang++
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(MSVC)
# debug information
if(DEBUG)
    if(MSVC)
    else(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
    endif(MSVC)
endif(DEBUG)
# compiler optimizations
if(RELEASE)
    if(MSVC)
    else(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    endif(MSVC)
endif(RELEASE)

################
# set exe output
################
add_executable(fullhearts ${SOURCES})

###########
# LIBRARIES
########### 
# find boost libs
# windows
if(WIN32)
endif(WIN32)
# linux
if(UNIX)
    # boost threads
    FIND_PACKAGE(Boost 1.65.1 COMPONENTS thread REQUIRED)
    TARGET_LINK_LIBRARIES(fullhearts LINK_PUBLIC ${Boost_LIBRARIES})
    # boost program_options
    FIND_PACKAGE(Boost 1.65.1 COMPONENTS program_options REQUIRED)
    TARGET_LINK_LIBRARIES(fullhearts LINK_PUBLIC ${Boost_LIBRARIES})
endif(UNIX)
