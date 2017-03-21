cmake_minimum_required (VERSION 2.8.4 )
project(cpp)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Wshadow")

add_executable( main main.cpp )
add_executable( class class.cpp )
add_executable( class2 class2.cpp )
add_executable( mc methodchaining.cpp )
add_executable( ab 
	ab.cpp
	Acla.cpp
	B.cpp )
add_executable( ref 
	ref.cpp )
add_executable( val 
	val.cpp )
add_executable( move 
	move.cpp )
add_executable( oper oper.cpp )
add_executable( cons cons.cpp )
add_executable( assign assign.cpp )
add_executable( inherit inherit.cpp )
add_executable( mapinterface mapinterface.cpp )
add_executable( sp sp.cpp )
add_executable( temp 
	temp.cpp
	Point.cpp
	 )
add_executable( stl stl.cpp 	Point.cpp )