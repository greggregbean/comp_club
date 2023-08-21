cmake_minimum_required (VERSION 3.0)

project (comp_club)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable ( run    src/main.cpp
                        include/comp_club.hpp
                        src/comp_club.cpp
)

if (MSVC)
    target_compile_options (
        run PRIVATE 
        /W4
    )

else ()
    target_compile_options (
        run PRIVATE
        -g -Wall -Wextra -pedantic -Werror
    )

endif ()