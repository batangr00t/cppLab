add_executable( world
	main.cpp
	Element.cpp
	ActiveObject.cpp
	ActivePoint.cpp
	BuilderRandom.cpp
	World.cpp
	Screen.cpp
	)
	
target_link_libraries( world
	log4cplus
	pthread
	ncurses
	)