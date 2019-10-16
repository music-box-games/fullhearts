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

file(GLOB spsrc "./*.cpp")
add_library(spaces ${spsrc})