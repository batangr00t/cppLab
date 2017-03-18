cmake_minimum_required (VERSION 2.8.4 )
project(asio)

#set(CMAKE_VERBOSE_MAKEFILE ON)
##set(CMAKE_CXX_FLAGS "-E -std=c++11 -g -Wall -Wshadow -fdump-tree-all")
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

find_library(log4cplus_location log4cplus)
message("log4cplus is at: ${log4cplus_location}")
find_package( Boost COMPONENTS system thread REQUIRED )
message("Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}" )
message("Boost_LIBRARIES = ${Boost_LIBRARIES}" )

include_directories( ${Boost_INCLUDE_DIR} )

add_subdirectory ( daytime )
add_subdirectory ( echo )
add_subdirectory ( http )
add_subdirectory ( intro )
