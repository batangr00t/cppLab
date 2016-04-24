cmake_minimum_required (VERSION 2.8	)
project(redis_client)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CPPLAB_PROGRAM main)

add_executable(${CPPLAB_PROGRAM} main.cpp RedisReply.cpp BinString.cpp )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -W -fpermissive")

find_library(lhiredis_location hiredis)
find_library(llog4cplus_location log4cplus)
message("hiredis is at: ${lhiredis_location}")
message("log4cplus is at: ${llog4cplus_location}")

target_link_libraries(${CPPLAB_PROGRAM} 
	${lhiredis_location}
	${llog4cplus_location}
	)

