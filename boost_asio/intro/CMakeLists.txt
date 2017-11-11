###################################
add_executable( sync_client sync_client.cpp )
target_link_libraries( sync_client ${Boost_LIBRARIES} )

###################################
add_executable( sync_server sync_server.cpp )
target_link_libraries( sync_server ${Boost_LIBRARIES} )

###################
add_executable( async_op async_op.cpp )
target_link_libraries( async_op ${Boost_LIBRARIES} )

###################
add_executable( print_reactor print_reactor.cpp )
target_link_libraries( print_reactor ${Boost_LIBRARIES} )