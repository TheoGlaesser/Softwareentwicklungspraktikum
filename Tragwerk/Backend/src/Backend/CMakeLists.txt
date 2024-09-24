cmake_minimum_required(VERSION 3.14)
project(Simulator)
set(SOURCES 
	Simulator.cpp
	Assembler.cpp
	Element.cpp
	)

add_executable(Simulator ${SOURCES})
