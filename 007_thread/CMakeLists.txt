cmake_minimum_required (VERSION 2.8.4 )
project(thread)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Wshadow -pthread")

add_executable( thread1 thread1.cpp )
add_executable( thread2 thread2.cpp )
add_executable( mutex mutex.cpp )
add_executable( future1 future1.cpp )
add_executable( future2 future2.cpp )
add_executable( task task.cpp )