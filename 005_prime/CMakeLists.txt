cmake_minimum_required (VERSION 2.8.4 )
project(prime)

add_executable( prime prime.cpp PrimeNumber.cpp )

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")