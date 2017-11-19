cmake_minimum_required( VERSION 2.8 )
project(cfcpp)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set( CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra" )

find_library( log4cpluslib log4cplus )
message( "log4cpluslib is ${log4cpluslib}" )

add_executable( calc
	main.cpp
	Token.cpp
	Calculator.cpp
	)

target_link_libraries( calc 
	${log4cpluslib}
	)
