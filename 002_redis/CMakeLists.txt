cmake_minimum_required (VERSION 2.8	)
project(redis)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

find_library(CPPLAB_hiredis hiredis)
find_library(CPPLAB_log4cplus log4cplus)
find_library(CPPLAB_event event)
message("hiredis is at: ${CPPLAB_hiredis}")
message("log4cplus is at: ${CPPLAB_log4cplus}")
message("libevent is at: ${CPPLAB_event}")

### main ( sync )
add_executable(main 
	main.cpp 
	RedisReply.cpp 
	BinString.cpp )
target_link_libraries(main 
	${CPPLAB_hiredis}
	${CPPLAB_log4cplus}
	)
	
### async	
add_executable(async 
	async.cpp 
	RedisReply.cpp 
	BinString.cpp )
target_link_libraries(async 
	${CPPLAB_hiredis}
	${CPPLAB_log4cplus}
	${CPPLAB_event}
	pthread
	)
