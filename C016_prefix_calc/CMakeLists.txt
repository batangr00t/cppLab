cmake_minimum_required( VERSION 2.8 )

project(cfcpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Wshadow")

add_executable( calc
	main.cpp
	Token.cpp
	Calculator.cpp
)
