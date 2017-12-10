enable_testing()
find_package( GTest REQUIRED )
message( "GTEST_LIBRARIES = ${GTEST_LIBRARIES}" )
include_directories(
	../src
	${GTEST_INCLUDE_DIRS}
	)


##### PointTest
add_executable(PointTest 
	PointTest.cpp
	../src/Point.cpp
	../src/PointBuilder.cpp
	../src/World.cpp
	)
	
target_link_libraries(PointTest 
	${GTEST_LIBRARIES}
	${log4cplus_lib}
	pthread
	)
