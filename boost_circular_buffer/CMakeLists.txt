cmake_minimum_required( VERSION 3.7 )
project( boost_circular_buffer )

#set( CMAKE_VERBOSE_MAKEFILE ON )

set ( CMAKE_CXX_FLAGS "-std=c++11 -g -Wall" )

find_package( Boost COMPONENTS system timer)
message("Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}" )
message("Boost_LIBRARIES = ${Boost_LIBRARIES}" )

include_directories( ${Boost_INCLUDE_DIR} )

##########
add_executable ( cb 
	main.cpp
)

target_link_libraries( cb
	${Boost_LIBRARIES}
)
