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

set(SOURCES_FILES_TESTS
        test/main_gtest.cpp
        test/test_nodes.cpp
        test/test_package.cpp
        test/test_storage_types.cpp
        )

add_executable(Net_Sim_ZPO_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(Net_Sim_ZPO_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

add_subdirectory(googletest-master)

target_link_libraries(Net_Sim_ZPO_test gmock)

target_compile_definitions(Net_Sim_ZPO_test PUBLIC EXERCISE_ID=EXERCISE_ID_NODES)





