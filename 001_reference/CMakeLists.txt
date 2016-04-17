cmake_minimum_required (VERSION 3.0)
project(ref)

add_executable( ref1 ref1.cpp Box.cpp )
add_executable( ref2 ref2.cpp Box.cpp )
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11")