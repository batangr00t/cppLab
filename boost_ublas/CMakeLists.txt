cmake_minimum_required(VERSION 3.7)
project( boost_ublas )

#set( CMAKE_VERBOSE_MAKEFILE on )
set( CMAKE_CXX_FLAGS "-std=c++11 -Wall" )

find_package( Boost COMPONENTS system REQUIRED )
message ( "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}" )
message ( "Boost_LIBRARIES = ${Boost_LIBRARIES}" )

include_directories( ${Boost_INCLUDE_DIRS} )

##### basic test create_matrix
add_executable ( create_matrix
	create_matrix.cpp
)

target_link_libraries( create_matrix
	${Boost_LIBRARIES}
)

#### operation of matrix
add_executable ( oper_matrix
	oper_matrix.cpp
)

target_link_libraries( oper_matrix
	${Boost_LIBRARIES}
) 

#### lu_fatorization
add_executable ( polyfit
	polyfit.cpp
)

target_link_libraries( polyfit
	${Boost_LIBRARIES}
) 
