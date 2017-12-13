add_executable( world
	main.cpp
	Point.cpp
	PointBuilder.cpp
	World.cpp
	)
target_link_libraries( world
	log4cplus
	)
	
target_include_directories( world PUBLIC
	src
	)
		