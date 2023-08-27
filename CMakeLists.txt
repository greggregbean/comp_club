cmake_minimum_required (VERSION 3.14)

project (comp_club)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

#-------------
# Main target
#-------------
add_executable (
    run 
    src/main.cpp
    src/comp_club.cpp
    src/input_check.cpp
    include/comp_club.hpp
    include/input_check.hpp
)

#---------
# Testing
#---------
enable_testing()
add_subdirectory(testing)
add_library(comp_club   src/comp_club.cpp)
add_library(input_check src/input_check.cpp)

#-----------------
# Compile options
#-----------------
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