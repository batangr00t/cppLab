cmake_minimum_required (VERSION 2.8.4 )
project(container)

add_executable( vec1 vector1.cpp Box.cpp)
add_executable( vec2 vector2.cpp Box.cpp)
add_executable( vec3 vector3.cpp Box.cpp)
add_executable( vec4 vector4.cpp Box.cpp)
add_executable( forward_list forward_list.cpp Box.cpp)
add_executable( map map.cpp Box.cpp)
add_executable( map2 map2.cpp Box.cpp)
add_executable( deque deque.cpp)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")