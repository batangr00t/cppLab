cmake_minimum_required (VERSION 2.8)
project(container)

add_executable( vec1 vector1.cpp Box.cpp)
add_executable( vec2 vector2.cpp Box.cpp)
add_executable( forward_list forward_list.cpp Box.cpp)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")