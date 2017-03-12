###################################	
add_executable( echo_client 
	echo_client.cpp
	)
	
target_link_libraries( echo_client 
	${Boost_LIBRARIES}
	${log4cplus_location}
	)

###################################
add_executable( echo_server 
	echo_server.cpp
	Session.cpp
	Server.cpp
	Request.cpp
	Response.cpp
)

target_link_libraries( echo_server
	${Boost_LIBRARIES}
	${log4cplus_location}
)