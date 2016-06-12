cmake_minimum_required (VERSION 2.8)
project(ref)

add_executable( ref1 ref1.cpp Box.cpp )
add_executable( ref2 ref2.cpp Box.cpp )
add_executable( ref3 ref3.cpp Box.cpp )
add_executable( ref4b ref4b.cpp Box.cpp )

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")