cmake_minimum_required( VERSION 2.8 )

project(active_object)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

add_executable( main
	main.cpp
	ActiveObject.cpp
	Sample.cpp
)

target_link_libraries( main
	log4cplus
	pthread
)