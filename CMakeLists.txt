cmake_minimum_required(VERSION 3.10.2) # cmake version

set(PRJ fullhearts) # project (solution) name
set(EXENAME fh) # exe name
set(DBG TRUE) # debug mode
set(LINK_TYPE)

# project name
project(${PRJ})

# load compiler setup script
include(./cmake_scripts/compiler_setup.cmake)

# load postbuild copy script
include(./cmake_scripts/postbuild_copy.cmake)

# load conan cmake file
set(CONAN_DISABLE_CHECK_COMPILER) # don't check compiler
message(STATUS "${CMAKE_SOURCE_DIR}")
if(EXISTS "${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake")
message(STATUS "Found conanbuildinfo at ${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake")
include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
elseif(EXISTS "${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake")
message(STATUS "Found conanbuildinfo at ${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake")
include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
elseif(EXISTS "${CMAKE_SOURCE_DIR}/build/build/conanbuildinfo.cmake")
message(STATUS "Found conanbuildinfo at ${CMAKE_SOURCE_DIR}/build/build/conanbuildinfo.cmake")
include(${CMAKE_SOURCE_DIR}/build/build/conanbuildinfo.cmake)
else()
message(ERROR " -- Could not find conanbuildinfo")
endif()
conan_basic_setup()

# add include paths
include_directories(./src/include)
include_directories(./ext_src/imgui)

# add subdirs
add_subdirectory(./src/components)
add_subdirectory(./src/core)
add_subdirectory(./src/log)
add_subdirectory(./src/utils)
add_subdirectory(./src/events)
add_subdirectory(./src/graphics)
add_subdirectory(./src/scenes)
add_subdirectory(./src/tests)
add_subdirectory(./src/factory)
add_subdirectory(./src/audio)
add_subdirectory(./src/ui)
add_subdirectory(./src/physics)


set(WLIBS components core log utils events graphics scenes tests factory audio ui physics)

# add root src
file(GLOB SOURCES "./src/*.cc")
file(GLOB EXTSOURCES "./ext_src/imgui/*.cpp")

# set ouput
add_executable(${EXENAME} ${SOURCES} ${EXTSOURCES})

# link subdirs
if(MSVC)
target_link_libraries(${EXENAME} ${WLIBS} ${CONAN_LIBS})
else()
target_link_libraries(${EXENAME} ${WLIBS} ${WLIBS} ${WLIBS} ${CONAN_LIBS})
endif()

# copy files to build folder
if(MSVC)
# if msvc, need to add bin folder to copy into
set(EXE_OUT_PATH ${CMAKE_BINARY_DIR}/bin)
else()
set(EXE_OUT_PATH ${CMAKE_BINARY_DIR})
endif()
pbcopy(${EXENAME} ${CMAKE_SOURCE_DIR}/shaders ${EXE_OUT_PATH}/shaders)
pbcopy(${EXENAME} ${CMAKE_SOURCE_DIR}/assets ${EXE_OUT_PATH}/assets)
pbcopy(${EXENAME} ${CMAKE_SOURCE_DIR}/data ${EXE_OUT_PATH}/data)

message(INFO "${EXE_OUT_PATH}")
