cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "-static")


set(SOURCE_FILES main.cpp)
add_executable(lab2 main.cpp readFileBlock.cpp readFileBlock.h writeFileBlock.cpp writeFileBlock.h grepBlock.cpp grepBlock.h dumpBlock.cpp dumpBlock.h sortBlock.cpp sortBlock.h replaceBlock.cpp replaceBlock.h worker.h blocksParser.cpp blocksParser.h workflow.cpp workflow.h)
target_link_libraries(lab2 ${CMAKE_EXE_LINKER_FLAGS})