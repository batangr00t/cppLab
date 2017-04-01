###################################
add_executable( sync_op sync_op.cpp )
target_link_libraries( sync_op ${Boost_LIBRARIES} )

###################
add_executable( async_op async_op.cpp )
target_link_libraries( async_op ${Boost_LIBRARIES} )