cmake_minimum_required (VERSION 2.8.4 )
project(prime)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

add_executable( prime prime.cpp PrimeNumber.cpp )
add_executable( factor factor.cpp )