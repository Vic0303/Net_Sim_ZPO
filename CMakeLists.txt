cmake_minimum_required(VERSION 3.24)
project(Net_Sim_ZPO)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp
        )

add_executable(Net_Sim_ZPO ${SOURCE_FILES} main.cpp)

target_include_directories(Net_Sim_ZPO PUBLIC include)

set(SOURCES_FILES_TESTS
        )

add_executable(my_project_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)


