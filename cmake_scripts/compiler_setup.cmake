# set c++ standard
set(CMAKE_CXX_STANDARD 17)

# set warning and error levels
if(MSVC)
add_compile_options(/W3)
else()
add_compile_options(-Werror -Wall -Wextra)
endif()

# add definitions for OS
if(WIN32)
add_compile_definitions(WINDOWS)
else()
endif()

# set debug mode
if(DBG)
add_compile_definitions(DEBUG)
endif()

# comdat
if(WIN32)
add_compile_options(/Gy)
endif()
