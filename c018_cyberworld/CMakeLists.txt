cmake_minimum_required( VERSION 2.8 )
project(cyberworld)
	
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

find_package( Boost COMPONENTS log )
message( "Boost_LIBRARIES = ${Boost_LIBRARIES}" )
add_definitions( -DBOOST_ALL_DYN_LINK )

add_subdirectory(src)
add_subdirectory(test)
	