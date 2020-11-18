cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(lab3 main.cpp optionparser.h baseOfGame.cpp baseOfGame.h map.cpp map.h interactivePlayer.cpp interactivePlayer.h optimalPlayer.cpp optimalPlayer.h randomPlayer.cpp randomPlayer.h player.cpp player.h)