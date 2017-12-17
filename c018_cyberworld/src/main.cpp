#include <log4cplus/configurator.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <chrono>
#include <thread>
#include <utility>
#include <ncurses.h>

#include "BuilderRandom.h"
#include "Define.h"
#include "Screen.h"
#include "World.h"

using namespace std;

int main(int argc, char*argv[]) {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");
	log4cplus::Logger logger = log4cplus::Logger::getInstance("main");

	int numberOfActiveObject = 5;
	if ( argc > 1 ) {
		numberOfActiveObject = atoi( argv[1] );
	}
	LOG4CPLUS_INFO( logger, "===== start " << numberOfActiveObject << " active objects");
	Screen screen;
	screen.showTitle(2000);
	{
		// create the world
		auto size = screen.getSize();
		World& world = World::getInstance();
		BuilderRandom builder{size.second/4.0, size.first/4.0};
		world.generatePoints(builder, numberOfActiveObject);

		// show the world
		//for ( int i = 0; i<(Hz*30); ++i ) {
		while( true ) {
			this_thread::sleep_for( chrono::milliseconds(1000/Hz) );
			int result = screen.showWorld();
			if ( result == ' ' ) break;
		}
	}
	screen.showEnding();

	// terminate the world
	LOG4CPLUS_INFO( logger, "===== end " );


    return 0;
}
