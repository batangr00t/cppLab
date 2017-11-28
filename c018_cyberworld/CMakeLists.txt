cmake_minimum_required( VERSION 2.8 )
project(cyberworld)
	
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

#find_package( Boost COMPONENTS )
#message( "Boost_LIBRARIES = ${Boost_LIBRARIES}" )
#add_definitions( -DBOOST_ALL_DYN_LINK )

find_library(log4cplus_lib log4cplus)
message("log4cplus is : ${log4cplus_lib}")

add_subdirectory(src)
add_subdirectory(test)
	