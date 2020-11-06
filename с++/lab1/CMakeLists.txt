cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(googletest)
enable_testing()

include_directories(googletest/include/gtest)

add_executable(lab1 main.cpp trit.cpp trit.h tritSet.cpp tritSet.h)

target_link_libraries(lab1 gtest gtest_main)
add_test(lab1 lab1)