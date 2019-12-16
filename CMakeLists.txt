cmake_minimum_required(VERSION 3.10.2)

set(PRJ fullhearts)
set(EXENAME fh)
set(DBG TRUE) # debug mode

# project name
project(${PRJ})

# load compiler setup script
include(./cmake_scripts/compiler_setup.cmake)

# load conan cmake file
include(./build/conanbuildinfo.cmake)
conan_basic_setup()

# add include paths
include_directories(./src/include)

# add subdirs
add_subdirectory(./src/components)
add_subdirectory(./src/core)
add_subdirectory(./src/log)
add_subdirectory(./src/utils)
add_subdirectory(./src/events)
add_subdirectory(./src/tests)
add_subdirectory(./src/graphics)
add_subdirectory(./src/input)

# add root src
file(GLOB SOURCES "./src/*.cc")

# set ouput
add_executable(${EXENAME} ${SOURCES})

# link subdirs
target_link_libraries(${EXENAME} components)
target_link_libraries(${EXENAME} core)
target_link_libraries(${EXENAME} log)
target_link_libraries(${EXENAME} utils)
target_link_libraries(${EXENAME} events)
target_link_libraries(${EXENAME} tests)
target_link_libraries(${EXENAME} graphics)
target_link_libraries(${EXENAME} input)

# link other libs
target_link_libraries(${EXENAME} ${CONAN_LIBS})
