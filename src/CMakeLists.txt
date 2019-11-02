cmake_minimum_required(VERSION 3.10.2)

set(PRJNME fullhearts)
set(EXENAME fh)
set(EXTRA_FLAGS "") # extra compile flags
set(DBG TRUE) # debug mode

# project name
project(${PRJNME})

# compiler flags
# debug/release mode
if(DBG)
if(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} /DDEBUG /D_DEBUG") # debug defines
set(EXTRA_FLAGS "${EXTRA_FLAGS} /Od /Zi") # turn off compiler opts and debug info on
# TODO: find way to set sln to debug build mode
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} -DDEBUG -D_DEBUG") # debug defines
set(EXTRA_FLAGS "${EXTRA_FLAGS} -O0 -g3") # turn off opt and turn on debug info
endif(MSVC)
else(DBG)
if(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} /DRELEASE /D_RELEASE") # release defines
set(EXTRA_FLAGS "${EXTRA_FLAGS} /O2") # 02 optimization
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} -DRELEASE -D_RELEASE") # release defines
set(EXTRA_FLAGS "${EXTRA_FLAGS} -O3 -g0") # 03 and no debug info
endif(MSVC)
endif(DBG)
# std version
if(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} /std:c++17")
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} --std=c++17")
endif(MSVC)
# platform defines
# win 32
if(WIN32)
if(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} /DWIN32 /D_WIN32")
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} -DWIN32 -D_WIN32")
endif(MSVC)
endif(WIN32)
# win 64
if(WIN64)
if(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} /DWIN64 /D_WIN64")
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} -DWIN64 -D_WIN64")
endif(MSVC)
endif(WIN64)
# linux
if(UNIX AND NOT APPLE)
if(MSVC) # for sake of redundancy
set(EXTRA_FLAGS "${EXTRA_FLAGS} /DLINUX /D_LINUX")
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} -DLINUX -D_LINUX")
endif(MSVC)
endif(UNIX AND NOT APPLE)
# macos
if(UNIX AND APPLE)
if(MSVC) # redundancy
set(EXTRA_FLAGS "${EXTRA_FLAGS} /DMACOS /D_MACOS")
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} -DMACOS -D_MACOS")
endif(MSVC)
endif(UNIX AND APPLE)
# warnings and errors
if(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} /W2") # /W2 because msvc warnings are weird
set(EXTRA_FLAGS "${EXTRA_FLAGS} /WX") # warnings are errors
else(MSVC)
set(EXTRA_FLAGS "${EXTRA_FLAGS} -Werror -Wextra -Wall")
endif(MSVC)

# add include paths
include_directories(./include)
include_directories(./core/include)
include_directories(./core/components)

# add subdirs
add_subdirectory(components)
add_subdirectory(core)

# add root src
file(GLOB SOURCES "./*.cc")

# set ouput
add_executable(${EXENAME} ${SOURCES})

# link subdirs
target_link_libraries(${EXENAME} components)
target_link_libraries(${EXENAME} core)

# link other libs
