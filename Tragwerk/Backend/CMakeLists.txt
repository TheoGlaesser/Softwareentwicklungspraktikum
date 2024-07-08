cmake_minimum_required(VERSION 3.5)

project(backend)

add_library(backend STATIC ${CMAKE_SOURCE_DIR}/src/Backend/Simulator.cpp) 

target_include_directories(backend PUBLIC ${CMAKE_SOURCE_DIR}/src/Backend.h)


