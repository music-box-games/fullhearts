# set c++ standard
set(CMAKE_CXX_STANDARD 17)

LINK_INTERFACE_MULTIPLICITY(10)

# set warning and error levels
if(MSVC)
add_compile_options(/W3)
else()
add_compile_options(-Wall -Wextra)
endif()

# add definitions for OS
if(WIN32)
add_compile_definitions(WINDOWS)
else()
endif()

# set debug mode
if(DBG)
#add_compile_definitions(DEBUG)
if(WIN32)
else()
add_compile_options(-DDEBUG)
endif()
endif()

# comdat
if(WIN32)
add_compile_options(/Gy)
endif()

# turn off warnings
if(MSVC)
else()
add_compile_options(-Wno-unused-function)
add_compile_options(-Wno-unused-private-field)
endif()

