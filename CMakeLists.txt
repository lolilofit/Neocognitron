cmake_minimum_required(VERSION 3.15)
project(neocognitron)

set(CMAKE_CXX_STANDARD 14)

add_executable(neocognitron main.cpp ImageProcess.cpp SCell.cpp CCell.cpp VCell.cpp DataOperations.cpp CLayer.cpp SLayer.cpp Neocognithron.cpp ColumnResult.cpp NeogognithronConfiguration.cpp)