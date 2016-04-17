cmake_minimum_required (VERSION 2.8)
project(redis_client)
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable( get get.cpp RedisReply.cpp )
#add_executable( set set.cpp )
#add_executable( pub pub.cpp )
#add_executable( sub sub.cpp )

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

find_library(lhiredis_location hiredis)
find_library(llog4cplus_location log4cplus)
message("hiredis is at: ${lhiredis_location}")
message("log4cplus is at: ${llog4cplus_location}")
target_link_libraries(get ${lib_location})
target_link_libraries(get ${llog4cplus_location})
