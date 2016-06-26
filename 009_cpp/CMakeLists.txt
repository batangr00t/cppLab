cmake_minimum_required (VERSION 2.8.4 )
project(cpp)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g ")

add_executable( oper oper.cpp )
add_executable( cons cons.cpp )
add_executable( assign assign.cpp )
add_executable( inherit inherit.cpp )
