cmake_minimum_required( VERSION 2.8 )
project(cyberworld)
	
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_subdirectory(src)
add_subdirectory(test)
	