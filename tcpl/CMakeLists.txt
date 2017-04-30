project(tcpl)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -pthread")

find_package( Boost COMPONENTS system timer)
message( "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}" )
message( "Boost_LIBRARIES = ${Boost_LIBRARIES}" )

include_directories( ${Boost_INCLUDE_DIR} )

add_executable( VectorTest
	VectorTest.cpp
	Vector.cpp
)

add_executable( MessageQueueTest
	MessageQueueTest.cpp
	Log.cpp
)

add_executable( AlgoPerfTest
	AlgoPerfTest.cpp
	${Boost_LIBRARIES}
)

target_link_libraries( AlgoPerfTest
	${Boost_LIBRARIES}
)

add_executable( NumericTest
	NumericTest.cpp
)

target_link_libraries( NumericTest
	${Boost_LIBRARIES}
)

