project(tcpl)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -pthread")

add_executable( VectorTest
	VectorTest.cpp
	Vector.cpp
)

add_executable( MessageQueueTest
	MessageQueueTest.cpp
	Log.cpp
)
