#####################
add_executable ( tcp_client
	tcp_client.cpp
	)
	
target_link_libraries( tcp_client
	${Boost_LIBRARIES}
	${log4cplus_location}
	)
	
########################
# A synchronous TCP daytime server
########################
add_executable ( server
	server.cpp
	)
	
target_link_libraries( server
	${Boost_LIBRARIES}
	${log4cplus_location}
	)