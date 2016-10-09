project(tcpl)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

#include_directories(  )

add_executable( vec
	main.cpp
	Vector.cpp
)