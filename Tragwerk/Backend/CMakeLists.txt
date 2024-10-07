cmake_minimum_required(VERSION 3.5)

project(backend)


set(SOURCES 
	src/Backend/Simulator.cpp
  src/Backend/Assembler.cpp
	src/Backend/Element.cpp
	)

add_library(backend STATIC ${CMAKE_SOURCE_DIR}/${SOURCES}) 

target_include_directories(backend PUBLIC ${CMAKE_SOURCE_DIR}/src/Backend.h)


