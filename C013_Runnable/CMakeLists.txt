cmake_minimum_required( VERSION 2.8 )

project(runnable)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wshadow")

find_library( log4cplus_location log4cplus )
message( "log4cplus_location = ${log4cplus_location}" )

add_executable( main
	main.cpp
	Runnable.cpp
	SampleRunnable.cpp
)

target_link_libraries( main
	${log4cplus_location}
)