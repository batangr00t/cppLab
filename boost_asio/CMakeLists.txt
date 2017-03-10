cmake_minimum_required (VERSION 2.8.4 )
project(asio)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Wshadow")

find_package( Boost COMPONENTS system thread REQUIRED )
message("Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}" )
message("Boost_LIBRARIES = ${Boost_LIBRARIES}" )

include_directories( ${Boost_INCLUDE_DIR} )

###################################	
add_executable( client
	client.cpp
	)

target_link_libraries( client 
	${Boost_LIBRARIES}
	)

###################################	
add_executable( echo_client echo_client.cpp	)
target_link_libraries( echo_client ${Boost_LIBRARIES} )

###################################
add_executable( echo_server 
	echo_server.cpp
	Session.cpp
	Server.cpp
)

target_link_libraries( echo_server ${Boost_LIBRARIES} )