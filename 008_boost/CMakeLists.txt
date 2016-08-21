cmake_minimum_required (VERSION 2.8.4 )
project(boost)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

find_package(Boost COMPONENTS system timer program_options  REQUIRED)
message("Boost_LIBRARIES is at: ${Boost_LIBRARIES}")

add_executable(  timer timer.cpp )
target_link_libraries(timer 
    ${Boost_LIBRARIES}
 	)
 	
add_executable(  po po.cpp )
target_link_libraries(po 
    ${Boost_LIBRARIES}
 	)
 	
add_executable(  exception exception.cpp )
target_link_libraries(exception 
    ${Boost_LIBRARIES}
 	)
 	