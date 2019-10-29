############################
# require cmake version 3.10
############################
cmake_minimum_required(VERSION 3.10.2)

set(DBG 1)
if(DBG)
    set(DEBUG 1)
    set(RELEASE 0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG")
else(DBG)
    set(DEBUG 0)
    set(RELEASE 1)
endif(DBG)

##################
# set project name
##################
project(fullhearts)

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
    # -std=c++17 for clang++/g++
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

###########################
# add dirs to include paths
###########################
include_directories(./include)
include_directories(${Boost_INCLUDE_DIR})

# add subdirs
add_subdirectory(components)
add_subdirectory(engine)
add_subdirectory(io)
add_subdirectory(messaging)
add_subdirectory(spaces)
add_subdirectory(threads)
add_subdirectory(trace)
add_subdirectory(utils)

##################
# add source files
##################
file(GLOB SOURCES "./*.cpp")

################
# set exe output
################
add_executable(fullhearts ${SOURCES})

###########
# LIBRARIES
########### 
# link subdirs
target_link_libraries(fullhearts components)
target_link_libraries(fullhearts engine)
target_link_libraries(fullhearts io)
target_link_libraries(fullhearts messaging)
target_link_libraries(fullhearts spaces)
target_link_libraries(fullhearts threads)
target_link_libraries(fullhearts trace)
target_link_libraries(fullhearts utils)

# find boost libs
set(Boost_DETAILED_FAILURE_MSG ON)
set(BOOST_ROOT "E:\\dev\\sdk\\boost_1_71_0")
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_DEBUG ON)
set(Boost_USE_MULTITHREADED ON)

FIND_PACKAGE(Boost 1.71.0 COMPONENTS thread program_options)
target_link_libraries(fullhearts ${Boost_LIBRARIES})
