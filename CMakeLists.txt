cmake_minimum_required(VERSION 3.10.2) # cmake version

set(PRJ fullhearts) # project (solution) name
set(EXENAME fh) # exe name
set(DBG TRUE) # debug mode
set(LINK_TYPE STATIC)

# project name
project(${PRJ})

# load compiler setup script
include(./cmake_scripts/compiler_setup.cmake)

# load postbuild copy script
include(./cmake_scripts/postbuild_copy.cmake)

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
add_subdirectory(./src/graphics)
add_subdirectory(./src/input)
add_subdirectory(./src/scenes)
add_subdirectory(./src/settings)
add_subdirectory(./src/tests)

# add root src
file(GLOB SOURCES "./src/*.cc")

# set ouput
add_executable(${EXENAME} ${SOURCES})

# link subdirs
if(MSVC)
target_link_libraries(${EXENAME} components core log utils events graphics input scenes settings tests)
else()
target_link_libraries(${EXENAME} -( components core log utils events graphics input scenes settings tests -) )
endif()

# link other libs
target_link_libraries(${EXENAME} ${CONAN_LIBS})

# copy files to build folder
if(MSVC)
# if msvc, need to add bin folder to copy into
set(EXE_OUT_PATH ${CMAKE_BINARY_DIR}/bin)
else()
set(EXE_OUT_PATH ${CMAKE_BINARY_DIR})
endif()
pbcopy(${EXENAME} ${CMAKE_SOURCE_DIR}/shaders ${EXE_OUT_PATH}/shaders)
pbcopy(${EXENAME} ${CMAKE_SOURCE_DIR}/assets ${EXE_OUT_PATH}/assets)
