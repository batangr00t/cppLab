cmake_minimum_required (VERSION 2.8)
project(stopwatch)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable( main main.cpp PerfWatch.cpp )

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
