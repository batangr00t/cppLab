###################################
add_executable( http_client client.cpp )
target_link_libraries( http_client ${Boost_LIBRARIES} )