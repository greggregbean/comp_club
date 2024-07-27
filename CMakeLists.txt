cmake_minimum_required (VERSION 3.14)

#---------------
# Project setup
#---------------
    project (comp_club)

#----------------------------
# Define include directories
#----------------------------
    set (COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
    include_directories (${COMMON_INCLUDES})

#--------------
# Source files
#--------------
    file (GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
    list (REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

#-------------------------------------
# Compile source files into a library
#-------------------------------------
    add_library (comp_club_lib ${SRC_FILES})

#------------------
# Main is separate
#------------------
    add_executable (run ${PROJECT_SOURCE_DIR}/src/main.cpp)

#----------------------------------
# linking Main against the library
#----------------------------------
    target_link_libraries (run comp_club_lib)

#-------------------
# Compilation flags
#-------------------
    set (CMAKE_CXX_STANDARD 20)
    set (CMAKE_CXX_STANDARD_REQUIRED ON)
    if (MSVC)
        target_compile_options (run PRIVATE  /W4)
    else ()
        target_compile_options (run PRIVATE  -g -Wall -Wextra -pedantic -Werror)
    endif ()

#---------
# Testing
#---------
    # google test is a git submodule for the project, and it is also cmake-based.
    add_subdirectory (googletest)

    enable_testing ()

    # Include the gtest library. gtest_SOURCE_DIR is available due to
    # 'project(gtest)' above.
    include_directories (${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    # Test file.
    file (GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/testing/testing.cpp)

    # Unit tests target.
    add_executable (run_unit_tests ${TEST_SRC_FILES})

    # Standard linking to gtest stuff.
    target_link_libraries (run_unit_tests gtest gtest_main)

    # Extra linking for the project.
    target_link_libraries (run_unit_tests comp_club_lib)

    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable run_unit_tests to see those specific tests.
    add_test (UnitTests run_unit_tests)
