add_executable( world
	main.cpp
	ActiveObject.cpp
	Point.cpp
	PointBuilderRandom.cpp
	World.cpp
	Screen.cpp
	)
	
target_link_libraries( world
	log4cplus
	pthread
	ncurses
	)

		