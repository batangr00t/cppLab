cmake_minimum_required (VERSION 2.8.4 )
project(log)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

find_library(log4cplus_location log4cplus)
message("log4cplus is at: ${log4cplus_location}")

add_executable( log
	main.cpp
)
	
target_link_libraries( log
	${log4cplus_location}
)