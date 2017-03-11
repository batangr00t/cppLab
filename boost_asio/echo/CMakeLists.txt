###################################	
add_executable( echo_client echo_client.cpp	)
target_link_libraries( echo_client ${Boost_LIBRARIES} )

###################################
add_executable( echo_server 
	echo_server.cpp
	Session.cpp
	Server.cpp
)
target_link_libraries( echo_server ${Boost_LIBRARIES} )