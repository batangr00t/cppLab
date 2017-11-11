cmake_minimum_required( VERSION 2.8 )

project(cfcpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wshadow")

function( gen exe_name )
	add_executable( ${exe_name}
		${exe_name}.cpp
	)
endfunction()

gen( mci_01 )
gen( mci_04 )
gen( mci_05 )
