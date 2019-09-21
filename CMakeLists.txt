# setup debug or release
set(DBG 1)

if(DBG)
set(DEBUG 1)
else(DBG)
set(RELEASE 0)
endif(DBG)

# require cmake version 3.10
cmake_minimum_required(VERSION 3.10)

# set project name
project(fullhearts)

# add include directory
include_directories(src/include)
include_directories(external/boost_1_71_0)

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

# add libraries
add_library(libboostthread STATIC IMPORTED)
set_target_properties(libboostthread PROPERTIES IMPORTED_LOCATION "./external/boost_1_71_0/bin.v2/libs/thread/build/msvc-14.1/debug/link-static/threadapi-win32/threading-multi/libboost_thread-vc141-mt-gd-x32-1_71.lib")
target_link_libraries(fullhearts libboostthread)


#if(WIN32)
#if(DEBUG)
#set_target_properties(libboostthread PROPERTIES IMPORTED_LOCATION "/external/boost_1_71_0/bin.v2/libs/thread/build/msvc-14.1/debug/link-static/threadapi-win32/threading-multi/libboost_thread-vc141-mt-gd-x32-1_71.lib")
#target_link_libraries(fullhearts libboostthread)
#endif(DEBUG)
#if(RELEASE)
#set_target_properties(libboostthread PROPERTIES IMPORTED_LOCATION "/external/boost_1_71_0/bin.v2/libs/thread/build/msvc-14.1/release/link-static/threadapi-win32/threading-multi/libboost_thread-vc141-mt-x32-1_71.lib")
#target_link_libraries(fullhearts libboostthread)
#endif(RELEASE)
#endif(WIN32)