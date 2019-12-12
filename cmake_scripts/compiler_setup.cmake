# set c++ standard
set(CMAKE_CXX_STANDARD 17)

# set warning and error levels
if(MSVC)
add_compile_options(/W3)
else()
add_compile_options(-Werror -Wall -Wextra)
endif()
