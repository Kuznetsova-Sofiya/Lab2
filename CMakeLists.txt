cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

find_package(GTest REQUIRED)

add_executable(test test.cpp)

target_link_libraries(test gtest gtest_main pthread dl)