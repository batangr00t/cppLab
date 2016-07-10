cmake_minimum_required (VERSION 2.8.4 )
project(timer)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

find_package( Boost COMPONENTS timer system REQUIRED )
message("Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}" )
message("Boost_LIBRARIES = ${Boost_LIBRARIES}" )

include_directories( ${Boost_INCLUDE_DIR} )

add_executable( main
	main.cpp
	)

target_link_libraries( main 
	${Boost_LIBRARIES}
	)
